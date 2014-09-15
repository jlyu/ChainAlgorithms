#pragma once

const int maxSize = 10;

template <class T>
class Queue {
public:
	Queue() { }
	~Queue() { }
	virtual bool EnQueue(const T &x) = 0;  //进队
	virtual bool DeQueue(T &x) = 0;        //出队
	virtual bool GetFront(T &x) = 0; //读取队头元素值
	virtual bool IsEmpty()const = 0; //判断队列是否空
	virtual bool IsFull()const = 0;  //判断队列是否满
	virtual int GetSize()const = 0;  //求队列元素个数
};