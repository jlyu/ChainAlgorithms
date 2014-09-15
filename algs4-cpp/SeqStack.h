#pragma  once
#include <assert.h>
#include "iostream"
using std::ostream;

//const int maxSize = 50;

template <class T>
class Stack {
public:
	Stack() { }
	virtual void Push(const T& x) = 0; //新元素进栈
	virtual bool Pop(T &x) = 0; //栈顶元素出栈，由x返回
	virtual bool GetTop(T &x)const = 0;//读取栈顶元素，由x返回
	virtual bool IsEmpty()const = 0; 
	virtual bool IsFull()const = 0;
	virtual int GetSize()const = 0; //计算栈中元素个数
};

const int StackIncreasement = 20; //栈溢出时扩展空间的增量

template <class T>
class SeqStack : public Stack<T> {
public:
	SeqStack(int sz=50); //建立一个空栈
	~SeqStack() { delete [] elements; }

	void Push(const T& x); //栈若有空间则插入元素x
	bool Pop(T &x); //若栈不为空则弹出元素x
	bool GetTop(T &x)const; 
	bool IsEmpty()const { return (top == -1) ? true : false; }
	bool IsFull()const { return (top == maxSize-1) ? true : false; }
	int GetSize()const { return top+1; }
	void Clear() { top = -1; }
	template <class T>
	friend ostream& operator<< (ostream& os, SeqStack<T>& s);

private:
	T *elements; //存放栈中的元素的栈数组
	int top;	 //栈顶指针
	int maxSize; //栈最大可容纳元素个数
	void overflowProcess(); //栈溢出处理
};

template <class T>
SeqStack<T>::SeqStack(int sz)
	:top(-1),maxSize(sz)
{
	elements = new T[maxSize];
	assert(elements != NULL);
}

template <class T>
void SeqStack<T>::overflowProcess() //栈溢出处理
{
	T *newElements = new T[maxSize + StackIncreasement];
	assert(newElements != NULL);
	for (int i=0; i<maxSize; ++i)
		newElements[i] = elements[i];
	maxSize += StackIncreasement;
	delete [] elements;
	elements = newElements;
	cout << "called SeqStack<T>::overflowProcess();" << "\n";
}

template <class T>
void SeqStack<T>::Push(const T& x) //栈若有空间则插入元素x
{
	if (IsFull())
		overflowProcess();
	elements[++top] = x;
}

template <class T>
bool SeqStack<T>::Pop(T &x) //若栈不为空则弹出元素x
{
	if (IsEmpty())
		return false;
	x = elements[top--];
	return true;
}

template <class T>
bool SeqStack<T>::GetTop(T &x)const
{
	if (IsEmpty())
		return false;
	x = elements[top];
	return true;
}

template <class T>
ostream& operator<< (ostream& os, SeqStack<T>& s)
{
	for (int i = s.top; i>=0; --i)
	{
		os << "[" << i << "]" << s.elements[i] << std::endl;
	}
	return os;
}