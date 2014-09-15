#pragma once
#include <iostream>
#include "LinkedStack.h"
#include "LinkedQueue.h"
using namespace std;

template <class T>
struct BinaryTreeNode {
	T data;
	BinaryTreeNode<T> *leftChild;
	BinaryTreeNode<T> *rightChild;
	BinaryTreeNode() : leftChild(NULL), rightChild(NULL) { }
	BinaryTreeNode(T x, BinaryTreeNode<T> *pl, BinaryTreeNode<T> *pr)
		: data(x), leftChild(pl), rightChild(pr) { }
	BinaryTreeNode(T x)
		: data(x), leftChild(NULL), rightChild(NULL) { }
};

template <class T>
class BinaryTree {
public:
	BinaryTree():root(NULL) { }
	BinaryTree(T val):RefValue(val), root(NULL) { }
	BinaryTree(BinaryTree<T> &bt) { root = Copy(bt.root); }
	~BinaryTree() { Destory(root); }
	//重载
	template <class T>
	friend int operator== (const BinaryTree<T> &s, const BinaryTree<T> &t) 
		{ return (equal(s.root, t.root))?true:false; }
	//指针
	BinaryTreeNode<T>* ReParent(BinaryTreeNode<T>* current) //返回父节点
		{ return (root==NULL || current==NULL) ? NULL : ReParent(root, current); }
	BinaryTreeNode<T>* ReLeftChild(BinaryTreeNode<T>* current)
		{ return (current==NULL)?current->leftChild : NULL; }
	BinaryTreeNode<T>* ReRightChild(BinaryTreeNode<T>* current)
		{ return (current==NULL)?current->rightChild : NULL; }
	BinaryTreeNode<T>* GetRoot()const { return root; }
	
	//属性
	bool IsEmpty() { return (root==NULL)? true : false; }
	int Height() { return Height(root); } //返回树高度
	int Size() { return Size(root); } //返回结点数
	
	//遍历
	void PreOrder(void(*visit)(BinaryTreeNode<T> *p))   { PreOrder(root, visit);   }
	void InfixOrder(void(*visit)(BinaryTreeNode<T> *p)) { InfixOrder(root, visit); }
	void PostOrder(void(*visit)(BinaryTreeNode<T> *p))  { PostOrder(root, visit);  }

	//操作
	int Insert(const T& item);
	BinaryTreeNode<T>* Find(T &item)const;
	void PrintBinTree(BinaryTreeNode<T> *subTree);
	void PrintBinTree_LevelOrder(BinaryTreeNode<T> *subTree);

protected:
	BinaryTreeNode<T> *root; //二叉树根指针
	T RefValue; //数据输入停止标记

protected:
	//建立摧毁
	void CreateBinaryTree(istream &in, BinaryTreeNode<T> *&subTree); //从文件读入建立树
	void Destory(BinaryTreeNode<T> *&subTree);
	BinaryTreeNode<T>* Copy(BinaryTreeNode<T> *OrigNode);
	
	//重载
	template <class T>
	friend istream& operator>> (istream&in, BinaryTree<T> &Tree);

	template <class T>
	friend ostream& operator<< (ostream&os, BinaryTree<T> &Tree);

	template <class T>
	friend bool equal(BinaryTreeNode<T> *a, BinaryTreeNode<T> *b);

	//指针
	BinaryTreeNode<T>* ReParent(BinaryTreeNode<T> *subTree, BinaryTreeNode<T> *current);

	//属性
	int Height(BinaryTreeNode<T> *subTree);
	int Size(BinaryTreeNode<T> *subTree);

	//遍历
	void PreOrder(BinaryTreeNode<T> *subTree, void(*visit)(BinaryTreeNode<T> *p));
	void InfixOrder(BinaryTreeNode<T> *subTree, void(*visit)(BinaryTreeNode<T> *p));
	void PostOrder(BinaryTreeNode<T> *subTree, void(*visit)(BinaryTreeNode<T> *p));

	//功能
	bool Insert(BinaryTreeNode<T> *&subTree, const T &x);
	bool Find(BinaryTreeNode<T> *&subTree, const T&x)const;
	BinaryTreeNode<T>* _Find(BinaryTreeNode<T> *&subTree, const T&x)const;
	void Traverse(BinaryTreeNode<T> *subTree, ostream &os);
};

template <class T>
void BinaryTree<T>::Destory(BinaryTreeNode<T> *&subTree)
{
	if (subTree!=NULL)
	{
		Destory(subTree->leftChild);
		Destory(subTree->rightChild);
		delete subTree;
	}
}

template <class T>
BinaryTreeNode<T>* BinaryTree<T>::ReParent(BinaryTreeNode<T> *subTree, BinaryTreeNode<T> *current)
{
	if (subTree == NULL) return NULL;
	if (subTree->leftChild == current || subTree->rightChild == current) return subTree;
	BinaryTree<T> *p;
	if ((p==ReParent(subTree->leftChild, current))!=NULL)
		return p;
	else
		return ReParent(subTree->rightChild, current);
}

template <class T>
void BinaryTree<T>::Traverse(BinaryTreeNode<T> *subTree, ostream &os)
{
	if (subTree!=NULL)
	{
		os << subTree->data << ' ';
		Traverse(subTree->leftChild, os);
		Traverse(subTree->rightChild, os);
	}
}

template <class T>
istream& operator>> (istream &in, BinaryTree<T> &Tree)
{  
	Tree.CreateBinaryTree(in, Tree.root);
	return in;
}

template <class T>
ostream& operator<< (ostream &os, BinaryTree<T> &Tree)
{
	Tree.Traverse(Tree.root, os);
	return os;
}

template <class T>
void BinaryTree<T>::CreateBinaryTree(istream &in, BinaryTreeNode<T> *&subTree) //从文件读入建立树
{
	//实现方法一：
	//利用广义表表示，配合stack读入二叉树
	//LinkedStack<BinaryTreeNode<char>* > s;
	//subTree = NULL;
	//BinaryTreeNode<char> *p, *t;
	//int k;
	//char ch;
	//in >> ch;
	//while (ch != RefValue)
	//{
	//	switch (ch)
	//	{
	//		case '(': s.Push(p); k=1; break;
	//		case ')': s.Pop(t); break;
	//		case ',': k=2; break;
	//		default: p = new BinaryTreeNode<char>(ch);
	//			if (subTree == NULL) subTree = p;
	//			else if (k==1)
	//			{
	//				s.GetTop(t);
	//				t->leftChild = p;
	//			}
	//			else
	//			{
	//				s.GetTop(t);
	//				t->rightChild = p;
	//			}
	//	}
	//	in >> ch;
	//}


	// 方法二： 利用二叉树前序遍历建立二叉树
	T item;
	if (!in.eof())
	{
		in >> item;
		if (item != RefValue)
		{
			subTree = new BinaryTreeNode<T>(item);
			assert(subTree!=NULL);
			CreateBinaryTree(in, subTree->leftChild);
			CreateBinaryTree(in, subTree->rightChild);
		}
		else
			subTree = NULL;
	}

}

template <class T>
void BinaryTree<T>::PreOrder(BinaryTreeNode<T> *subTree, void(*visit)(BinaryTreeNode<T> *p))
{
	if (subTree!=NULL)
	{
		visit(root);
		PreOrder(subTree->leftChild, visit);
		PreOrder(subTree->rightChild, visit);
	}
}

template <class T>
void BinaryTree<T>::InfixOrder(BinaryTreeNode<T> *subTree, void(*visit)(BinaryTreeNode<T> *p))
{
	if (subTree!=NULL)
	{
		InfixOrder(subTree->leftChild, visit);
		visit(root);
		InfixOrder(subTree->rightChild, visit);
	}
}

template <class T>
void BinaryTree<T>::PostOrder(BinaryTreeNode<T> *subTree, void(*visit)(BinaryTreeNode<T> *p))
{
	if (subTree!=NULL)
	{
		PostOrder(subTree->leftChild, visit);
		PostOrder(subTree->rightChild, visit);
		visit(root);
	}
}

template <class T>
int BinaryTree<T>::Size(BinaryTreeNode<T> *subTree)
{
	if (subTree==NULL) return 0;
	else return 1+Size(subTree->leftChild)+Size(subTree->rightChild);
}

template <class T>
int BinaryTree<T>::Height(BinaryTreeNode<T> *subTree)
{
	if (subTree==NULL) return 0;
	else
	{
		int i = Height(subTree->leftChild);
		int j = Height(subTree->rightChild);
		return (i<j) ? j+1 : i+1;
	}
}

template <class T>
BinaryTreeNode<T>* BinaryTree<T>::Copy(BinaryTreeNode<T> *OrigNode)
{
	if (OrigNode==NULL) return NULL;
	BinaryTreeNode<T> *temp = new BinaryTreeNode<T>;
	temp->data = OrigNode->data;
	temp->leftChild = Copy(OrigNode->leftChild);
	temp->rightChild = Copy(OrigNode->rightChild);
	return temp;
}

template <class T>
bool equal(BinaryTreeNode<T> *a, BinaryTreeNode<T> *b)
{
	if (a == NULL && b==NULL) return true;
	if (a != NULL && b!=NULL && a->data == b->data && equal(a->leftChild, b->leftChild) && (a->rightChild,b->rightChild))
		return true;
	else
		return false;
}

template <class T>
void BinaryTree<T>::PrintBinTree(BinaryTreeNode<T> *subTree)
{
	if (subTree!=NULL)
	{
		cout << subTree->data;
		if (subTree->leftChild!=NULL || subTree->rightChild!=NULL)
		{
			cout << "(";
			PrintBinTree(subTree->leftChild);
			cout << ",";
			if (subTree->rightChild!=NULL)
				PrintBinTree(subTree->rightChild);
			cout << ")";
		}
	}
}

int _pow(int a, int b)
{
	int result=0;
	if (b<0)
	{
		return a;
	}
	for (int i=0; i!=b; ++i)
	{
		a *= a;
	}
	return a;
}

template <class T>
void BinaryTree<T>::PrintBinTree_LevelOrder(BinaryTreeNode<T> *subTree)
{
	static int cnt = 0;
	LinkedQueue<BinaryTreeNode<T>* > Q;
	BinaryTreeNode<T> *p= subTree;
	Q.EnQueue(p);
	while (!Q.IsEmpty())
	{
		Q.DeQueue(p);
		cout << p->data << " ";
		cnt++;
		for (int i=0; i<10; ++i)
		{
			if (cnt==_pow(2,i)-1)
			{
				cout << " | ";
				break;
			}
		}
		
		if (p->leftChild!=NULL) Q.EnQueue(p->leftChild);
		if (p->rightChild!=NULL) Q.EnQueue(p->rightChild);
	}
}