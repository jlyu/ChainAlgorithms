#include "String.h"
#include <iostream>

String::String(int sz)
	: maxSize(sz)
{
	cha = new char[maxSize+1];
	assert(cha != NULL);
	curLen = 0;
	cha[0] = '\0';
}

String::String(const char *init)
{
	int len = strlen(init);
	maxSize = (len>defaultSize) ? len : defaultSize;
	cha = new char[maxSize+1];
	assert(cha != NULL);
	for (int i=0; i<len; ++i)
	{
		cha[i] = *init;
		init++;
	}
	//strcpy(cha, init);
	curLen = len;
	cha[len] = '\0';
}

String::String(const String& obj)
{
	maxSize = obj.maxSize;
	cha = new char[maxSize+1];
	assert(cha!=NULL);
	curLen = obj.curLen;
	strcpy(cha, obj.cha);
}

String String::operator() (int pos, int len) //从pos所指出位置开始连续取len个字符返回子串
{
	String temp;
	if (pos<0 || pos+len-1>=maxSize || len<0)
	{
		temp.curLen = 0;
		temp.cha[0] = '\0';
	}
	else
	{
		if (pos+len-1>=curLen) len = curLen - pos;
		temp.curLen = len;
		for (int i=0, j=pos; i<len; ++i,++j) temp.cha[i] = cha[j];		
		temp.cha[len] = '\0';
	}
	return temp;  //导致返回临时变量？
}

String& String::operator= (String& obj) //重载赋值操作符
{
	//if (*this != obj)
	if (&obj != this)
	{
		delete [] cha;
		cha = new char[obj.maxSize];
		assert(cha!=NULL);
		curLen = obj.curLen;
		strcpy(cha, obj.cha);
	}
	return *this;
}

String& String::operator+= (String& obj)
{
	int newLen = curLen+obj.curLen;
	if (maxSize >= newLen)
	{
		strcat(cha, obj.cha);
	}
	else
	{
		char *temp = cha;
		cha = new char[newLen];
		assert(cha!=NULL);
		strcpy(cha,temp);
		strcat(cha,obj.cha);
		maxSize = newLen;
		delete [] temp;
	}
	curLen = newLen;
	return *this;
}

char& String::operator[](int i) //取*this的第i个字符
{
	if (i<0 || i>=curLen)
	{
		std::cerr << "下标越界！"<< std::endl;
		return cha[maxSize-1];
	}
	return cha[i];
}

int String::Find(String& pat)const //子串匹配
{
	int i, j;
	for (i=0; i<=curLen-pat.curLen; ++i)
	{
		for (j=0; j<pat.curLen; ++j)
		{
			if (cha[i+j]!=pat.cha[j])
				break;
			if (j==pat.curLen-1)
				return i;
		}
	}
	return -1;
}

int String::KMP_Find(String& pat, int next[])const
{
	int PatternPos = 0, TargetPos = 0; //两个串的扫描指针
	int PatternLen = pat.curLen;
	int TargetLen = curLen;

	while (PatternPos<PatternLen && TargetPos<TargetLen)
	{
		if (PatternPos==-1 || pat.cha[PatternPos]==cha[TargetPos])
		{
			PatternPos++;
			TargetPos++;
		}
		else	
			PatternPos = next[PatternPos];
	}
	if (PatternPos<PatternLen)
		return -1;
	else
		return TargetPos-PatternLen;
}

void String::GetNext(int next[])
{
	int j=0; 
	int k=-1;
	int ParttenLen = curLen;
	next[0]=-1;
	while (j<ParttenLen)
	{
		if (k==-1 || cha[j]==cha[k])
		{
			j++; k++;
			next[j] = k;
		}
		else
			k = next[k];
	}
}