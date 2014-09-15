#pragma once
#include "Queue.h"

template <class T>
class Deque : public Queue<T> {
public:
	virtual bool GetHead(T& x)const = 0;
	virtual bool GetTail(T& x)const = 0;
	virtual bool EnQueue(const T &x);
	virtual bool EnQueueHead(const T &x) = 0;
	virtual bool EnQueueTail(const T &x) = 0;
	virtual bool DeQueue(T &x);
	virtual bool DeQueueHead(T &x) = 0;
	virtual bool DeQueueTail(T &x) = 0;
}; 


template <class T>
bool Deque<T>::EnQueue(const T &x)
{
	return EnQueueTail(const T &x);
}

template <class T>
bool Deque<T>::DeQueue(T &x)
{
	T temp;
	bool tag = DeQueueHead(temp);
	x = temp;
	return tag;
}