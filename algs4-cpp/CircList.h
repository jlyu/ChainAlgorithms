#pragma once
#include <iostream>

template <class T>
struct CircLinkNode {
	T data;
	CircLinkNode<T> *next;
	CircLinkNode(CircLinkNode<T> *ptr = NULL): next(ptr) { }
	CircLinkNode(T d, CircLinkNode<T> *ptr = NULL): data(d), next(ptr) { }
};

template <class T>
class CircList : public CircLinkNode<T>{
public:
	CircList();
	CircList(const T& up, const T& down);
	CircList(const T& x);
	CircList(CircList<T> &L);
	~CircList();
	int Length()const;
	bool IsEmpty() { return first->next == first ? true : false; } //判断链表是否为空
	CircList<T>* GetHead()const { return first; } //返回循环链表的头指针
	void SetHand(CircLinkNode<T> *p);  //设置附加头结点地址
	CircLinkNode<T>* Search(T x); //搜索含x的结点
	CircLinkNode<T>* Locate(int i); //搜索第i个结点的值
	T* GetData(int i);		//取得第i个元素的值
	bool Insert(T &x); // 插入x
	bool Insert(int i, T &x); //在第i个元素后插入x
	bool Remove(int i, T &x); //删除第i个结点，x返回该值
	void Output();

//private:
public:
	CircLinkNode<T> *first; //循环链表头结点
	CircLinkNode<T> *last;  //循环链表尾结点
};

template <class T>
CircList<T>::CircList()
{
	first = new CircLinkNode<T>(0);
	last = new CircLinkNode<T>(0);
	first->next = last;
	last->next = first;
}

template <class T>
CircList<T>::CircList(const T& x)
{
	first = new CircLinkNode<T>(x);
	last = new CircLinkNode<T>(x);
	first->next = last;
	last->next = first;
}

template <class T>
CircList<T>::CircList(const T& l, const T& r)
{
	first = new CircLinkNode<T>(l);
	last = new CircLinkNode<T>(r);
	first->next = last;
	last->next = first;

	for (int i=r-1; i>=l+1; --i) Insert(i);
}
template <class T>
CircList<T>::~CircList()
{
	CircLinkNode<T> *delPtr;
	while(first->next != first)
	{
		delPtr = first->next;
		first->next = delPtr->next;
		delete delPtr;
	}
}

template <class T>
int CircList<T>::Length()const
{
	int len = 0;
	CircLinkNode<T>* current = first->next;
	while (current->next!=first)
	{
		current = current->next;
		len++;
	}
	return len;
}

template <class T>
CircLinkNode<T>* CircList<T>::Locate(int i) //搜索第i个结点的值
{
	if (i<0)
		return NULL;
	int count = 0;
	CircLinkNode<T> *current = first;
	//i = i % Length();
	//while (count != i)
	while (current!=first && count<i)
	{
		current = current->next;
		count++;
	}
	return current;
}

template <class T>
bool CircList<T>::Insert(int i, T &x) //在第i个元素后插入x
{
	CircLinkNode<T> *current = Locate(i);
	CircLinkNode<T>* newNode = new CircLinkNode<T>(x);
	if (newNode==NULL) return false;
	if (Length() == 0)
	{
		first->next = newNode;
		newNode->next = last;
	}
	else if (current==first || current == last)
	{
		newNode->next = last->next;
		last->next = newNode;
	}
	else
	{
		newNode->next = current->next;
		current->next = newNode;
	}
	return true;
}

template <class T>
bool CircList<T>::Insert(T &x) //在第i个元素后插入x
{
	CircLinkNode<T>* newNode = new CircLinkNode<T>(x);
	if (newNode == NULL) return false;
	if (Length()==0)
	{
		newNode->next = last;
		first->next = newNode;
	}
	else
	{
		//newNode->next = last->next;
		//last->next = newNode;
		newNode->next = first->next;
		first->next = newNode;
	}
	
	return true;
}

template <class T>
void CircList<T>::Output()
{
	CircLinkNode<T> *current = first;
	std::cout << first->data << "(" << &first->data <<  ")" << std::endl;
	std::cout << last->data  << "(" << &last->data  <<  ")" << std::endl; 
	int cnt = 0;
	while (current->next!=first)
	//while (cnt != 20)
	{
		//if (current!=first && current!=last)
		{
			std::cout << current->data << "(" << &current->data <<  "),";
			
		}
		current = current->next;
		cnt++;
	}
	std::cout << std::endl;
}