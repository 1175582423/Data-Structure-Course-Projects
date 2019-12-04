//二叉树结点与二叉树

#pragma once // 避免同一个文件被include多次

#include <iostream> // NULL在这里面

// 二叉树结点结构体
template <class ElemType>
struct BinTreeNode {
	ElemType data;
	BinTreeNode<ElemType>* left; // 肯定回答
	BinTreeNode<ElemType>* right; // 否定回答

	BinTreeNode(); // 无参构造函数
	BinTreeNode(const ElemType& val, BinTreeNode<ElemType>* l_child = NULL, BinTreeNode<ElemType>* r_child = NULL); // 含参构造函数
};

template <class ElemType>
BinTreeNode<ElemType>::BinTreeNode() {
	left = right = NULL;
}

template<class ElemType>
BinTreeNode<ElemType>::BinTreeNode(const ElemType& val, BinTreeNode<ElemType>* l_child, BinTreeNode<ElemType>* r_child) {
	data = val;
	left = l_child;
	right = r_child;
}


//二叉树类
template <class ElemType>
class BinaryTree {
protected:
	BinTreeNode<ElemType>* root; // 根结点
	void Destroy(BinTreeNode<ElemType>*& r); // 析构函数的辅助函数
public:
	BinaryTree(); // 构造函数
	BinaryTree(BinTreeNode<ElemType>* r); // 带参构造函数
	~BinaryTree(); // 析构函数
	BinTreeNode<ElemType>* getRoot() const; // 返回根结点

};

template<class ElemType>
void BinaryTree<ElemType>::Destroy(BinTreeNode<ElemType>*& r) {
	if (r != NULL) {
		Destroy(r->left);
		Destroy(r->right);
		delete r;
		r = NULL;
	}
}

template<class ElemType>
BinaryTree<ElemType>::BinaryTree() {
	root = NULL;
}

template<class ElemType>
BinaryTree<ElemType>::BinaryTree(BinTreeNode<ElemType>* r) {
	root = r;
}

template<class ElemType>
BinaryTree<ElemType>::~BinaryTree() {
	Destroy(root);
}

template<class ElemType>
inline BinTreeNode<ElemType>* BinaryTree<ElemType>::getRoot() const
{
	return root;
}