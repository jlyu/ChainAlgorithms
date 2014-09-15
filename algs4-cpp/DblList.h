#pragma once
#include <iostream>

template <class T>
struct DblNode{
	T data;
	DblNode<T> *lLink; //双链表前驱链接
	DblNode<T> *rLink; //双链表后驱链接

	DblNode(DblNode<T> *left =NULL, DblNode<T> *right = NULL)
		:lLink(left),rLink(right)
	{  }
	DblNode(T val, DblNode<T> *left =NULL, DblNode<T> *right = NULL)
		:data(val), lLink(left),rLink(right)
	{  }
};

template <class T>
class DblList : public DblNode<T> {
public:
	DblList(T uniqueVal); //构造函数，建立附加头结点
	~DblList(); //析构函数
	int Length()const; //计算双链表长度
	bool isEmpty(){ return first->rLink== first; } //判断双链表是否为空
	DblNode<T>* GetHead()const { return first; } //得到双链表头结点
	void SetHead(DblNode<T>* ptr) { first = ptr; } //设置双链表的头结点
	DblNode<T>* Search(const T& x); //在链表中沿后继方向寻找等于给定值x的结点
	DblNode<T>* Locate(int i, int d); //d=0前驱方向，≠0按后驱方向定位序号为i的结点
	bool Insert(int i, const T& x, int d); //d=0前驱方向，≠0按后驱方向, 在序号为i的结点之后插入一个x值的结点
	bool Remove(int i, const T& x, int d); //d=0前驱方向，≠0按后驱方向, 删除序号为i的结点。删除值传给x
	void Output(); //输出
private:
	DblNode<T> *first; 
};


template <class T>
DblList<T>::DblList(T uniqueVal) //构造函数，建立附加头结点
{
	first = new DblNode(uniqueVal);
	if (first == NULL)
	{
		std::cerr << "头结点内存分配失败！";
		exit(1);
	}
	first->rLink = first->lLink = first;
}

template <class T>
DblList<T>::~DblList() //析构函数
{

}

template <class T>
int DblList<T>::Length()const //计算双链表长度
{
	int len = 0;
	DblNode<T> *current = first;
	while (current->rLink!=first)
	{
		len++;
		current = current->rLink;
	}
	return len;
}

template <class T>
DblNode<T>* DblList<T>::Search(const T& x) //在链表中沿后继方向寻找等于给定值x的结点
{ //顺序搜索
	DblNode<T> *current = first->rLink;
	while (current != first && current->data != x)
		current = current->rLink;
	if (current!=first)
		return current;
	else
		return NULL;
}

template <class T>
DblNode<T>* DblList<T>::Locate(int i, int d) //d=0前驱方向，≠0按后驱方向定位序号为i的结点
{
	if (i<0)
		return NULL;
	if (first->rLink == first || i==0)
		return first;
	DblNode<T> *current; 
	if (d==0)  //决定方向
		current = first->lLink;
	else
		current = first->rLink;
	for (int j=1; j<i; j++)
	{
		if (current==first) 
			break;
		else if (d==0) 
			current = current->lLink;
		else 
			current = current->rLink;
	}
	if (current!=first)
		return current; //定位成功
	else
		return NULL; //定位失败
}

template <class T>
bool DblList<T>::Insert(int i, const T& x, int d) //d=0前驱方向，≠0按后驱方向, 在序号为i的结点之后插入一个x值的结点
{
	DblNode<T> *newNode = new DblNode(x);
	if (newNode==NULL) return false;

	DblNode<T> *current;
	if (isEmpty()) //如果双链表为空，则直接插入
	{
		//current = first;
		//newNode->rLink = 
		current = first;
	}
	else
		current = Locate(i, d);
	if (current==NULL) return false;

	if (d==0) //前驱插入，至少修改4个指针
	{
		newNode->lLink = current->lLink;
		current->lLink = newNode;
		newNode->lLink->rLink = newNode;
		newNode->rLink = current;
	}
	else
	{
		newNode->rLink = current->rLink;
		current->rLink = newNode;
		newNode->rLink->lLink = newNode;
		newNode->lLink = current;
	}
	return true;
}

template <class T>
bool DblList<T>::Remove(int i, const T& x, int d) //d=0前驱方向，≠0按后驱方向, 删除序号为i的结点。删除值传给x
{
	DblNode<T> *current = Locate(i, d);
	if (current==NULL) return false;
	current->lLink = current->rLink;
	current->rLink = current->lLink;
	x = current->data; delete current;
	return true;
}

template <class T>
void DblList<T>::Output() //输出
{
	DblNode<T> *current = first->rLink;
	while (current != first)
	{
		std::cout << current->data << ",";
		current = current->rLink;
	}
	std::cout << '\n';
}