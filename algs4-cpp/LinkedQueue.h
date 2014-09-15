#include "Queue.h"
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
class LinkedQueue : public Queue<T> {
public:
	LinkedQueue() : front(NULL) , rear(NULL) { }
	~LinkedQueue() { Clear(); }
	bool EnQueue(const T &x);
	bool DeQueue(T &x);
	bool GetFront(T &x);
	void Clear();
	bool IsEmpty()const { return (front == rear) ? true : false; }
	int GetSize()const;
	
	template <class T>
	friend ostream& operator<< (ostream &os, LinkedQueue<T> &lq);

protected:
	LinkNode<T> *front;  //队头指针
	LinkNode<T> *rear;   //队尾指针
};

template <class T>
void LinkedQueue<T>::Clear()
{
	LinkNode<T> *delNode;
	while (front!=NULL)
	{
		delNode = front;
		front = delNode->next;
		delete delNode;
	}
}

template <class T>
bool LinkedQueue<T>::EnQueue(const T &x)
{
	if (front==NULL) //链式队列为空
	{
		rear = new LinkNode<T>(x);
		front = rear;
		if (front == NULL) 
			return false;
	}
	else
	{
		rear->next = new LinkNode<T>(x);
		assert(rear->next!=NULL);
		rear = rear->next;
	}
}

template <class T>
bool LinkedQueue<T>::DeQueue(T &x)
{
	if (IsEmpty()) return false;
	LinkNode<T> *delNode = front;
	x = front->data;
	front = delNode->next;
	delete delNode;
	return true;
}

template <class T>
bool LinkedQueue<T>::GetFront(T &x)
{
	if (IsEmpty()) return false;
	x = front->data;
	return true;
}

template <class T>
int LinkedQueue<T>::GetSize()const 
{
	int cnt = 0;
	LinkNode<T> *current = front;
	while (current != NULL)
	{
		cnt++;
		current = current->next;
	}
	return cnt;
}

template <class T>
ostream& operator<< (ostream &os, LinkedQueue<T> &lq)
{
	os << "队列中元素个数： " << lq.GetSize() << std::endl;
	LinkNode<T> *current = lq.front;
	int i=0;
	while (current!=NULL)
	{
		os << "[" << ++i << "]" << current->data << std::endl;
		current = current->next;
	}
	return os;
}