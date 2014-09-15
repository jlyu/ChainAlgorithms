#pragma once

#include <iostream>
#include <assert.h>

template <class T>
struct GenListNode;

template <class T>
struct Items { //返回值的类结构定义
	int utype; //=0/1/2
	union {
		int ref; //=0,附加头结点，存放引用计数
		T value; //=1,存放数据
		GenListNode<T> *hlink; //=2,存放指向子表的头结点指针
	} info;
	Items() : utype(0), info.ref(0) { }
	Items(Items<T>& copy) { utype = copy.utype; info = copy.info; }
};

template <class T>
class GenListNode { //广义表结点类定义
public:
	GenListNode():utype(0), tlink(NULL), info.ref(0) { }
	GenListNode(GenListNode<T> &gl)
	{ utype = gl.utype; tlink = gl.tlink; info = gl.info; }
private:
	int utype;
	GenListNode<T> *tlink; //指向同一层下一个结点的指针
	union {
		int ref;
		T value;
		GenListNode<T> *hlink;
	} info;
};

template <class T>
class GenList { //广义表类定义
	template <class T>
	friend std::istream& operator>> (std::istream &in, GenList<T> &gl);
public:
	GenList();
	~GenList();
	bool Head(Items& x); //返回表头元素x
	bool Tail(GenList<T> &lt); //返回表尾lt
	GenListNode<T>* Front(); //返回第一个元素
	GenListNode<T>* Next(GenListNode<T>* elem); //返回表元素elem的直接后续元素
	void Copy(const GenList<T> &gl);
	int Length(); //计算广义表的长度
	int Depth();  //计算非递归广义表的深度

private:
	GenListNode<T> *Copy(GenListNode<T> *gl); //复制一个gl指示的无共享非递归表
	int Length(GenListNode<T> *gl); //求由gl指示的广义表的长度
	int depth(GenListNode<T> *gl); //计算由gl指示的非递归表的深度
	bool equal(GenListNode<T> *ls, GenListNode<T> *rs); //判断分别以ls，rs为头结点的2个广义表是否相等
	void Remove(GenListNode<T> *gl); //释放以gl为头结点的广义表
	void GreateList(std::istream &in, GenListNode<T> *&gl);
private:
	GenListNode<T> *first; //广义表头指针
};

template <class T>
GenList<T>::GenList()
{
	first = new GenListNode;
	assert(first!=NULL);
}

template <class T>
bool GenList<T>::Head(Items& x) //返回表头元素x
{
	if (first->tlink == NULL) return false;
	else 
	{
		x.utype = first->utype;
		x.info = first->info;
		return true;
	}
}

template <class T>
bool GenList<T>::Tail(GenList<T> &lt)
{
	if (first->tlink == NULL) return false; //空表
	else 
	{
		lt.first->utype = 0;
		lt.first->info.ref = 0;
		lt.first->tlink = Copy(first->tlink->tlink);
		return true;
	}
}