#pragma once
#include <iostream>
using namespace std;

template <class T>
struct LinkNode { //单链表结点结构
	T data;
	LinkNode<T> *next;

	LinkNode<T> (LinkNode<T> *ptr = NULL) { next = ptr; }
	LinkNode<T> (T item, LinkNode<T> *ptr= NULL) { data = item; next = ptr; }
};

template <class T>
class List : public LinkNode<T>{
public:
	List() { first = new LinkNode<T>; }
	List(const T& x) { first = new LinkNode<T>(x); }
	List(List<T>& L); //复制构造函数
	~List() { makeEmpty();} //析构函数
	void makeEmpty();  //链表置空
	int Length()const; //计算链表长度
	LinkNode<T> *getHead()const { return first; } //获得链表头指针
	LinkNode<T> *Search(T x);     //搜索链表中含X的元素
	LinkNode<T> *Locate(int i);   //搜索第i个元素的地址
	bool getData(int i, T&x)const; //取得第i个结点的值
	void setData(int i, T&x);      //设置第i个结点的值
	bool Insert(int i, T&x);       //在第i个结点后插入x
	bool Remove(int i, T&x);       //删除第i个结点，x返回删除值
	bool IsEmpty()const { return(first->next==NULL)? true : false; } //链表是否为空
	//bool IsFull()const { return false; } //链表是否溢出
	void Sort(); //链表排序
	void Input(); 
	void Output();

protected:
	LinkNode<T> *first; //链表的头指针
};

template <class T>
List<T>::List(List<T>& L) //复制构造函数
{
	T copyV;
	List<T> *srcPtr = L.getHead();
	List<T> *destPtr = first = new List<T>;
	while (srcPtr->next != NULL)
	{
		copyV = srcPtr->next->data;
		destPtr->next = new List<T>(copyV);
		destPtr = destPtr->next;
		srcPtr = srcPtr->next;
	}
	destPtr->next = NULL;
}

template<class T>
void List<T>::makeEmpty()  //链表置空
{
	LinkNode<T> *p;
	if (IsEmpty())
	{
		p = first->next;
		first->next = p->next;
		delete p;
	}
}

template <class T>
int List<T>::Length()const //计算链表长度
{
	int length = 0;
	LinkNode<T> *tmpp = first->next;
	while (tmpp!=NULL)
	{
		length++;
		tmpp = tmpp->next;
	}
	return length;
}

template <class T>
LinkNode<T>* List<T>::Search(T x)     //搜索链表中含X的元素
{
	LinkNode<T>* current = first->next;
	while (current!=NULL)
	{
		if (current->getData == x)
			break;
		else
			current = current->next;
	}
	return current;
}

template <class T>
LinkNode<T>* List<T>::Locate(int i)   //搜索第i个元素的地址
{
	if (i<0 || i>Length())
		return NULL;
	LinkNode<T> *current = first;
	int count = 0;
	while (current!=NULL && count<i)
	{
		current = current->next;
		count++;
	}
	return current;
}

template <class T>
bool List<T>::getData(int i, T&x)const //取得第i个结点的值
{
	if (i<=0 || i>Length())
		return false;

	LinkNode<T> *current = Locate(i);
	if (current == NULL)
		return false;
	else
	{
		x = current->data;
		return true;
	}
}

template <class T>
void List<T>::setData(int i, T&x)      //设置第i个结点的值
{
	if (i<=0)
		return;
	LinkNode<T> *current = Locate(i);
	if (current == NULL)  //超出链表尾部范围，其实这里可以插入
		return;
	else
		current->data = x;
}

template <class T>
bool List<T>::Insert(int i, T&x)       //在第i个结点后插入x
{
	LinkNode<T> *current = Locate(i);
	if (current == NULL)
		return false;
	LinkNode<T> *newNode = new LinkNode<T>(x);
	newNode->next = current->next;
	current->next = newNode;
	return true;
}

template <class T>
bool List<T>::Remove(int i, T&x)
{
	LinkNode<T> *current = Locate(i-1);
	if (current == NULL || current->next == NULL)
		return false;
	LinkNode<T> *delNode = current->next;
	x = delNode->data;
	current->next = delNode->next;
	delete delNode;
	return true;
}

template <class T>
void List<T>::Output()
{
	LinkNode<T> *header = first->next;
	if (IsEmpty())
	{
		cout << "单链表为空" << endl;
		return;
	}
	while (header != NULL)
	{
		cout << header->data << ",";
		header = header->next;
	}
	cout << endl;	
}

template <class T>
void List<T>::Input()
{//前插法
	if (!IsEmpty())
		makeEmpty();
	cout << "当输入1111时，停止插入"<< endl;

	LinkNode<T> *newNode;
	T val;
	cin >> val;
	while (val != 1111)
	{
		newNode = new LinkNode<T>(val);
		if (newNode == NULL)
		{
			cerr << "新结点分配内存错误！" << endl;
			return;
		}
		newNode->next = first->next;
		first->next = newNode;
		cin >> val;
	}
}