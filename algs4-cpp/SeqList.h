#include <iostream>
#include "LinearLine.h"

const int defaultSize = 100;
template <class T>
class SeqList : public LinearLine<T> {
protected:
	T *data; //放数组，用动态分配
	int maxSize; //最大可容纳元素个数
	int last; //当前已存的最后位置（从0开始）
public:
	void reSize(int newSize); //改变data空间大小

public:
	SeqList(int sz = defaultSize); //构造函数，带默认参数
	SeqList(SeqList<T> &sl);       //复制构造函数
	~SeqList() { delete [] data; } 

	int Size() const { return maxSize; }    //表最大体积
	int Length() const { return last+1; } //表长度
	int Search(T& x) const; //搜索表中给定值x，返回位置
	int Locate(int i) const; //定位表中第i个元素的位置
	bool getData(int i, T& x) const; //取第i个的值
	void setData(int i, T& x);  //修改第i个的值为x
	bool Insert(int i, T& x); //在第i个元素后插入x
	bool Remove(int i, T& x); //删除第i个，通过x返回(？)
	bool IsEmpty() const;  //判断表是否为空
	bool IsFull() const;   //判读表是否为满
	void Sort();   //排序
	void Input();  //输入
	void Output(); //输出
	//SeqList<T> operator= (SeqList<T>& L); //重载赋值操作符
};

template<class T>
SeqList<T>::SeqList(int sz = defaultSize) //构造函数，带默认参数
{
	maxSize = defaultSize;
	last = -1;
	data = new T[maxSize];
	if (data == NULL)
	{
		std::cerr << "数组空间分配失败！" << endl;
		exit(1);
	}
}


template <class T>
SeqList<T>::SeqList(SeqList<T> &sl)       //复制构造函数
{
	maxSize = sl.Size();
	last = sl.Length()-1;
	data = new T[maxSize];
	if (data == NULL)
	{
		std::cerr << "数组空间分配失败！" << endl;
		exit(1);
	}

	T tmp;
	for (int i=1; i<=last+1; ++i)
	{
		sl.getData(i, tmp);
		data[i-1] = tmp;
	}
}

template <class T>
void SeqList<T>::reSize(int newSize) //改变data空间大小
{
	if (newSize <= 0)
	{
		cerr << "无效的数组大小" << endl;
		return;
	}

	if (newSize == maxSize)
	{
		cerr << "新的数组大小与原来的无变化" << endl;
		return;
	}

	if (IsEmpty())
	{
		delete [] data;
		maxSize = newSize;
		data = new T[maxSize];
		if (data == NULL)
		{
			std::cerr << "数组空间分配失败！" << endl;
			exit(1);
		}
	}
	else 
	{
		T *newArray = new T[newSize];
		if (newArray == NULL)
		{
			std::cerr << "数组空间分配失败！" << endl;
			exit(1);
		}
		int n = last +1;
		T *srcptr = data; //源数组首地址
		T *dstptr = newArray; //目的数组首地址
		while(n--)
			*dstptr++ = *srcptr++;
		delete [] data;
		data = newArray;
		maxSize = newSize;
	}
}

template <class T>
int SeqList<T>::Search(T& x) const //搜索表中给定值x，返回位置
{
	for (int i=0; i<=last; ++i)
	{
		if (data[i]==x)
		{
			return i+1;
		}
	}
	return 0;
};

template <class T>
int SeqList<T>::Locate(int i) const //定位表中第i个元素的位置
{
	if (i>=1 && i<=last+1)
	{
		return i;
	}
	return 0;
}

template <class T>
bool SeqList<T>::getData(int i, T& x) const //取第i个的值
{ 
	if (i>0 && i<=last+1) 
	{ 
		x = data[i-1]; 
		return true;
	}
	else
		return false;
}

template <class T>
void SeqList<T>::setData(int i, T& x)  //修改第i个的值为x
{
	if (i>0 && i<=last+1)
	{
		data[last+1] = x;
	}
}

template <class T>
bool SeqList<T>::Insert(int i, T& x) //在第i个元素后插入x
{ 
	if (last == maxSize-1) return false;
	if (i<0 || i>last+1) return false;
	for (int j=last; j>=i; --j)
	{
		data[j+1] = data[j];
	}
	data[i] = x;
	last++;
	return true;
}

template <class T>
bool SeqList<T>::Remove(int i, T& x) //删除第i个，通过x返回(？)
{ 
	if (last == -1) return false;
	if (i<1 || i>last+1) return false;
	x = data[i-1];
	for (int j=i; j<=last; ++j)
	{
		data[j-1] = data[j];
	}
	last--;
	return true;
}

template <class T>
bool SeqList<T>::IsEmpty() const  //判断表是否为空
{ return (last==-1) ? true : false; }

template <class T>
bool SeqList<T>::IsFull() const   //判读表是否为满
{ return (last==maxSize-1) ? true : false; }

template <class T>
void SeqList<T>::Sort()   //排序
{ }


template <class T>
void SeqList<T>::Input()  //输入
{//从标准输入键盘逐个数据输入，建立顺序表
	cout << "开始建立数序表，请输入表中元素个数：";
	while (1)
	{
		std::cin >> last; 
		if (last <= maxSize-1)
		{
			break;
		}
		cout << "范围错误，不能超过"<< maxSize - 1 << endl;
	}
	for (int i = 0; i<=last; ++i)
	{
		//cin >> data[i];//
		//自动从0顺序输入
		data[i] = i;
		cout << i+1 << endl;
	}
}

template <class T>
void SeqList<T>::Output() //输出
{//顺序将表内全部元素输出到屏幕上
	cout << "顺序表当前元素的最后位置为：" << last << endl;
	for (int i = 0; i<=last ; i++)
	{
		cout << "#" << i+1 << ":" << data[i] << endl;
	}
}

//SeqList<T> operator= (SeqList<T>& L); //重载赋值操作符

