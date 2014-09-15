#pragma once
#include "Deque.h"
#include "CirQueue.h"

template <class T>
class CirDeque : public Deque<T>, public CirQueue<T>{
public:
	CirDeque(int sz = 10); //构造函数
	~CirDeque() { 
		if (elements!=NULL)
			delete [] elements; 
	} //析构函数
	bool EnQueue(const T &x); //若队列不满，则x进队，否则做溢出处理
	bool EnQueueHead(const T &x);
	bool EnQueueTail(const T &x);

	bool DeQueue(T &x); //若队列不空，则返回true和x的值，否则返回false
	bool DeQueueHead(T &x);
	bool DeQueueTail(T &x);

	bool GetHead(T& x)const;
	bool GetTail(T& x)const;

	void MakeEmpty() { front = rear = 0; } //置空操作：队头指针和队尾指针置0
	bool IsEmpty()const { return (front == rear)? true : false; }
	bool IsFull()const { return ((rear+1)%maxSize == front) ? true : false; }
	int GetSize()const { return(rear-front+maxSize)%maxSize; }
	void Output()const;
	template <class T>
	friend ostream& operator<< (ostream &os, CirQueue<T> &cq);

protected:
	int front, rear; //队头和队尾指针
	T *elements;     //存放队列元素的数组
	int maxSize;     //队列最大可容纳元素个数
}

template <class T>
bool CirDeque<T>::GetHead(T& x)const
{
	T temp;
	bool tag = CirQueue<T>::GetFront(temp);
	x = temp;
	return tag;
}

template <class T>
bool CirDeque<T>::EnQueueTail(const T &x)
{
	return CirQueue<T>::EnQueue(x);
}

template <class T>
bool CirDeque<T>::DeQueueHead(T &x)
{
	T temp;
	bool tag = CirQueue<T>::DeQueue(temp);
	x = temp;
	return tag;
}

template <class T>
bool CirDeque<T>::GetTail(T& x)const
{
	if (IsEmpty()) return false;
	x = elements[(rear-1+maxSize) % maxSize];
	return true;
}

template <class T>
bool CirDeque<T>::EnQueueHead(const T& x) 
{
	if (IsFull())return false;
	front = (front-1+maxSize)%maxSize;
	elements[front] = x;
	return true;
}

template <class T>
bool CirDeque<T>::DeQueueTail(T &x)
{
	if (IsEmpty()) return false;
	rear = (rear -1 +maxSize)%maxSize;
	x = elements[rear];
	return true;
}