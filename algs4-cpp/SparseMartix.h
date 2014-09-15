#include <iostream>
#include <assert.h>
using namespace std;

//稀疏矩阵的三元组表的类定义
template <class T>
struct Trituple{  //三元组类Trituple
	int row; //行号
	int col; //列号
	T value; //非零元素值
	Trituple<T>& operator= (Trituple<T>& x)
	{ row = x.row; col = x.col; value = x.value; }
};

template <class T>
class SparseMartix {
	template <class T>
	friend ostream& operator<< (ostream &os, SparseMartix<T> &M);

	template <class T>
	friend istream& operator>> (istream &in, SparseMartix<T> &M);

public:
	SparseMartix(int maxSz = 100);
	SparseMartix(SparseMartix<T>& x);
	~SparseMartix() { delete [] smArray; }
	SparseMartix<T>& operator= (SparseMartix<T>& x);
	SparseMartix<T> Transpose(); //转置
	SparseMartix<T> Add(SparseMartix<T> &b); //当前矩阵与矩阵b相加
	SparseMartix<T> Multiply(SparseMartix<T> &b); //c[i][j]=∑(a[i][k]*b[k][j])实现当前矩阵与矩阵b相乘
private:
	int _Rows;  //稀疏矩阵的行
	int _Cols;  //稀疏矩阵的列
	int _Terms; //稀疏矩阵中非零个数
	Trituple<T> *smArray;
	int maxTerms;
};

template <class T>
SparseMartix<T>::SparseMartix(int maxSz)
	: maxTerms(maxSz)
{
	assert(maxSz > 0);
	smArray = new Trituple<T>[maxSz];
	assert(smArray!=NULL);
	_Rows = _Cols = _Terms = 0;
}

template <class T>
SparseMartix<T>::SparseMartix(SparseMartix<T>& x)
{
	_Rows = x._Rows;
	_Cols = x._Cols;
	_Terms = x._Terms;
	maxTerms = x.maxTerms;
	smArray = new Trituple<T>[maxTerms];
	assert(smArray!=NULL);
	for (int i=0; i<_Terms; ++i)
	{
		smArray[i] = x.smArray[i];
	}
}

template <class T>
ostream& operator<< (ostream &os, SparseMartix<T> &M)
{
	os << "rows = " << M._Rows << std::endl;
	os << "cols = " << M._Cols << std::endl;
	os << "Nonzero terms = " << M._Terms << std::endl;
	for (int i=0; i<M._Terms; ++i)
	{
		os << "M[" <<M.smArray[i].row << "][" << M.smArray[i].col
		   <<"]=" << M.smArray[i].value << std::endl;
	}
	return os;
}

template <class T>
istream& operator>> (istream& in, SparseMartix<T>& M)
{
	in >> M._Rows >> M._Cols >> M._Terms;
	if (M._Terms > M.maxTerms)
	{
		cerr << "Number of terms overflow!" << endl;
		exit(1);
	}
	for (int i=0; i<M._Terms; ++i)
	{
		cout << "Enter row, column, and value of term:" << i+1 << endl;
		in  >> M.smArray[i].row  >> M.smArray[i].col >> M.smArray[i].value;
	}
	return in;
}

template <class T>
SparseMartix<T> SparseMartix<T>::Transpose() //转置
{
	SparseMartix<T> b(maxTerms);
	b._Rows = _Cols;
	b._Cols = _Rows;
	b._Terms = _Terms;
	if (_Terms > 0)
	{
		int k, i, currentB = 0;
		for (k = 0; k<_Cols; ++k)
		{
			for (i = 0; i<_Terms; ++i)
			{
				if (smArray[i].col == k)
				{
					b.smArray[currentB].row = k;
					b.smArray[currentB].col = smArray[i].col;
					b.smArray[currentB].value = smArray[i].value;
					currentB++;
				}
			}
		}
	}
	return b;
}