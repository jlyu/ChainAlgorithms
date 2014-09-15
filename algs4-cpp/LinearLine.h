#pragma once

template <class T>
class LinearLine {
public:
	LinearLine(){ }
	~LinearLine(){ }
	virtual int Size() const = 0;   //表最大体积
	virtual int Length() const = 0; //表长度
	virtual int Search(T& x) const = 0; //搜索表中给定值x，返回位置
	virtual int Locate(int i) const = 0; //定位表中第i个元素的位置
	virtual bool getData(int i, T& x) const = 0; //取第i个的值
	virtual void setData(int i, T& x) = 0;  //修改第i个的值为x
	virtual bool Insert(int i, T& x) = 0; //在第i个元素后插入x
	virtual bool Remove(int i, T& x) = 0; //删除第i个，通过x返回(？)
	virtual bool IsEmpty() const = 0;  //判断表是否为空
	virtual bool IsFull() const = 0;   //判读表是否为满
	virtual void Sort() = 0;   //排序
	virtual void Input() = 0;  //输入
	virtual void Output() = 0; //输出
	//virtual LinearLine<T> operator= (LinearLine<T>& L) = 0; //重载赋值操作符
};