#pragma once
#include <assert.h>
#include <iostream>
using std::ostream;

template <class T>
class Stack {
public:
	Stack() { }
	virtual void Push(const T& x) = 0; //新元素进栈
	virtual bool Pop(T &x) = 0; //栈顶元素出栈，由x返回
	virtual bool GetTop(T &x)const = 0;//读取栈顶元素，由x返回
	virtual bool IsEmpty()const = 0; 
	//virtual bool IsFull()const = 0;
	virtual int GetSize()const = 0; //计算栈中元素个数
};

template <class T>
struct LinkNode { //单链表结点结构
	T data;
	LinkNode<T> *next;
	
	LinkNode<T> (LinkNode<T> *ptr = NULL) { next = ptr; }
	LinkNode<T> (T item, LinkNode<T> *ptr= NULL) { data = item; next = ptr; }
};

template <class T>
class LinkedStack : public Stack<T> {
public:
	LinkedStack():top(NULL) { }
	~LinkedStack() { Clear(); }
	void Push(const T& x); //进栈
	bool Pop(T &x); //退栈
	bool GetTop(T &x)const; //读取栈顶元素
	bool IsEmpty()const { return (top==NULL)?true:false; }
	int GetSize()const; //求栈内元素个数
	void Clear(); //清栈
	
	template <class T>
	friend ostream& operator<< (ostream& os, LinkedStack<T>& LS);

private:
	LinkNode<T> *top; //栈顶指针，即链表头指针
};

template <class T>
void LinkedStack<T>::Clear() //清栈
{
	while (top != NULL) //每次删除头结点逐个释放栈
	{
		LinkNode<T>* delNode = top;
		top = top->next;
		delete delNode;
	}
}

template <class T>
void LinkedStack<T>::Push(const T& x) //进栈
{
	LinkNode<T>* newNode = new LinkNode<T>(x);
	assert(newNode!=NULL);
	newNode->next = top;
	top = newNode;
	//top = new LinkNode<T>(x, top);
	//assert(top!=NULL);
}

template <class T>
bool LinkedStack<T>::Pop(T &x) //退栈
{
	if (IsEmpty())	return false;
	LinkNode<T>* delNode = top;
	x = top->data;
	top = top->next;
	delete delNode;
	return true;
}

template <class T>
bool LinkedStack<T>::GetTop(T &x)const //读取栈顶元素
{
	if (IsEmpty()) return false;
	x = top->data;
	return true;
}

template <class T>
int LinkedStack<T>::GetSize()const
{
	if (IsEmpty()) return 0;
	int cnt = 0;
	LinkNode<T> *current = top;
	while (current != NULL)
	{
		cnt++;
		current = current->next;
	}
	return cnt;
}

template <class T>
ostream& operator<< (ostream&os, LinkedStack<T> &ls)
{          
	if (ls.IsEmpty())
	{
		os << "空栈" << std::endl;
		return os;
	}
	LinkNode<T> *current = ls.top; 
	int cnt = 1;
	while (current != NULL)          
	{                                
		os << "[" << cnt << "]:" << current->data << "\n";
		current = current->next;
		cnt++;
	}
	os << std::endl;
	return os;
}