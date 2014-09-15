#pragma once
#include "Queue.h"
#include <assert.h>
#include <iostream>
using namespace std;


template <class T>
class CirQueue : public Queue<T> {
public:
	CirQueue(int sz = 10); //构造函数
	~CirQueue() { 
		if (elements!=NULL)
			delete [] elements; 
	} //析构函数
	bool EnQueue(const T &x); //若队列不满，则x进队，否则做溢出处理
	bool DeQueue(T &x); //若队列不空，则返回true和x的值，否则返回false
	bool GetFront(T &x); //若队列不为空，则返回队头元素和true，否则返回false
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
};

template <class T>
CirQueue<T>::CirQueue(int sz)//构造函数
	: front(0), rear(0), maxSize(sz)
{
	elements = new T[maxSize];
	assert(elements!=NULL);
}

template <class T>
bool CirQueue<T>::EnQueue(const T &x) //若队列不满，则x进队，否则做溢出处理
{
	if (IsFull()) return false;
	elements[rear] = x;
	rear = (rear+1) % maxSize; //队尾指针+1
	return true;
}

template <class T>
bool CirQueue<T>::DeQueue(T &x)
{
	if (IsEmpty()) return false;
	x = elements[front];
	front = (front+1) % maxSize;
	return true;
}

template <class T>
bool CirQueue<T>::GetFront(T &x) //若队列不为空，则返回队头元素和true，否则返回false
{
	if (IsEmpty()) return false;
	x = elements[front];
	return true;
}

template <class T>
ostream& operator<< (ostream &os, CirQueue<T> &cq)
{
	os << "front = " << cq.front << " rear = " << cq.rear << std::endl;
	for (int i = cq.front; i!=cq.rear; i=(i+1)%cq.maxSize)
	{
		os << "[" << i << "]" << cq.elements[i] << std::endl;
	}
	return os;
}

template <class T>
void CirQueue<T>::Output()const
{
	std::cout << "front = " << front << " rear = " << rear << std::endl;
	for (int i = front; i!=rear; i=(i+1)%maxSize)
	{
		std::cout << "[" << i << "]" << elements[i] << std::endl;
	}
}