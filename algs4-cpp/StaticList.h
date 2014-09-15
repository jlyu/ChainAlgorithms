#pragma once
#include <iostream>

const int maxSize = 10;
template <class T>
struct StaticLinkNode {
	T data;
	int link;  //结点连接指针
};

template <class T>
class StaticList {
public:
	void InitList(); //初始化
	int Length();    //计算静态链表的长度
	int Search(T x);  //在静态链表中查找具有给定值的结点
	int Locate(int i); //在静态链表中查找第i个结点
	bool Append(T x); //在静态链表的表尾追加一个新结点
	bool Insert(int i, T x); //在静态链表的第i个位置结点后插入一个新结点
	bool Remove(int i); //在静态链表中释放第i个结点
	bool IsEmpty(); //判断静态链表是否为空
	void Output(); //输出显示
private:
	StaticLinkNode<T> elem[maxSize];
	int currHead; //当前可分配空间的首地址
};

template <class T>
void StaticList<T>::InitList()
{
	elem[0].link = -1;
	currHead = 1;
	 //当前可分配空间从1开始建立带表头结点的空链表
	for (int i=1; i<maxSize-1; ++i)
	{
		elem[i].link = i+1; //构成空闲链表
	}
	elem[maxSize-1].link = -1; //链表尾
}

template <class T>
int StaticList<T>::Length()
{
	int len = 0;
	for (int i=0; i<maxSize; ++i)
	{
		if (elem[i].link == -1)
		{
			break;
		}
		len++;
	}
	return len;
}

template <class T>
int StaticList<T>::Search(T x)  //在静态链表中查找具有给定值的结点
{
	int ptr = elem[0].link; //起始指针
	while (ptr!=-1)
	{
		if (elem[ptr].data == x)
			break;
		else
			ptr = elem[ptr];
	}
	return ptr;
}

template <class T>
int StaticList<T>::Locate(int i) //在静态链表中查找第i个结点
{
	if (i<0) return -1;
	if (i==0) return 0;
	int cnt = 1;
	int p = elem[0].link;
	while (p!=-1 && cnt<i)
	{
		p = elem[p].link;
		cnt++;
	}
	return p;
}

template <class T>
bool StaticList<T>::Append(T x) //在静态链表的表尾追加一个新结点
{
	if (currHead==-1) return false;
	int q = currHead;
	currHead = elem[currHead].link;
	elem[q].data = x;
	elem[q].link = -1;
	int p = 0; //寻找表尾
	while (elem[p].link != -1)
	{
		p = elem[p].link;
	}
	elem[p].link = q;
	return true;
}

template <class T>
bool StaticList<T>::Insert(int i, T x) //在静态链表的第i个位置结点后插入一个新结点
{
	int p = Locate(i);
	if (p==-1) return false; 
	int q = currHead;
	currHead = elem[currHead].link;
	elem[q].data = x;
	elem[q].link = elem[p].link; //链入
	elem[p].link = q;
	return true;
}

template <class T>
bool StaticList<T>::Remove(int i) //在静态链表中释放第i个结点
{
	int p = Locate(i-1);
	if (p == -1) return false;
	int q = elem[p].link;
	elem[p].link = elem[q].link;
	elem[q].link = currHead;
	currHead = q;
	return true;
}

template <class T>
bool StaticList<T>::IsEmpty() //判断静态链表是否为空
{
	return (elem[0].link==-1) ? true: false;
}

template <class T>
void StaticList<T>::Output() //输出显示
{
	for (int i =0; i<maxSize; ++i)
	{
		std::cout <<"[" <<elem[i].link << "]" << elem[i].data << ",";
	}
	std::cout << std::endl;
}