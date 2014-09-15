#pragma once
#include <assert.h>
#include <iostream>

template <class T>
class PriorityQueue {
public:
	PriorityQueue(int sz = 10);
	~PriorityQueue() { delete [] pqelements; }
	bool Insert(const T& x); //将新元素x插入队尾
	bool RemoveMin(T &x); //将队头元素删去
	bool GetFront(T &x)const; //读取队头（具有最小优先权）的值
	void MarkEmpty() { const = 0; } //置最小优先级队列为空
	bool IsEmpty() { return (count==0) ? true : false; }
	bool IsFull() { return (count==maxSize) ? true : false; }
	int GetSize()const { return count; }
	void Output();

protected:
	T* pqelements; //优先级队列数组
	int count;     //当前元素个数
	int maxSize;   //队列最大可容纳元素个数
	void _AdjustPriorityQueue(); //队列调整
};


template <class T>
PriorityQueue<T>::PriorityQueue(int sz)
	: count(0), maxSize(sz)
{
	pqelements = new T[maxSize];
	assert(pqelements!=NULL);
}

template <class T>
bool PriorityQueue<T>::Insert(const T& x) //将新元素x插入队尾
{
	if (IsFull()) return false;
	pqelements[count++] = x;
	_AdjustPriorityQueue();
	return true;
}

template <class T>
void PriorityQueue<T>::_AdjustPriorityQueue()
{
	T temp = pqelements[count-1];
	int j;
	for (j = count-2; j>=0; --j)
	{
		if (pqelements[j]<=temp)
		{
			break;
		}
		else
		{
			pqelements[j+1] = pqelements[j];
		}
	}
	pqelements[j+1] = temp;
}

template <class T>
bool PriorityQueue<T>::RemoveMin(T &x) //将队头元素删去
{
	if (IsEmpty()) return false;
	x = pqelements[0];
	for (int i=1; i<count; ++i)
		pqelements[i-1] = pqelements[i]; //删除队头，全体左移
	count--;
	return true;
}

template <class T>
bool PriorityQueue<T>::GetFront(T &x)const //读取队头（具有最小优先权）的值
{
	if (IsEmpty()) return false;
	x = pqelements[0];
	return true;
}

template <class T>
void PriorityQueue<T>::Output()
{
	for (int i=0; i<count; ++i)
	{
		std::cout << "[" << i << "]" << pqelements[i] << std::endl;
	}
}