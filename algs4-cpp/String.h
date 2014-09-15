#pragma once
#include <assert.h>
#include <string.h>

#define defaultSize 128

class String {
public:
	String(int sz = defaultSize);
	String(const char *init);
	String(const String& obj);
	~String() { delete [] cha; }
	int GetLength() { return curLen; }
	String operator() (int pos, int len); //从pos所指出位置开始连续取len个字符返回子串
	int operator== (String& obj)const { return strcmp(cha, obj.cha); }
	int operator!= (String& obj)const { return !(*this==obj); }
	int operator!()const { return curLen == 0; } //判断串是否空
	String& operator= (String& obj); //重载赋值操作符
	String& operator+= (String& obj);
	char& operator[](int i); //取*this的第i个字符
	int Find(String& pat)const; //子串匹配
	int KMP_Find(String& pat, int next[])const; 
	void GetNext(int next[]);

private:
	char *cha;   //串存放数组
	int curLen;  //当前串的实际长度
	int maxSize; //字符字符数组最大
};