//����������������

#pragma once // ����ͬһ���ļ���include���

#include <iostream> // NULL��������

// ���������ṹ��
template <class ElemType>
struct BinTreeNode {
	ElemType data;
	BinTreeNode<ElemType>* left; // �϶��ش�
	BinTreeNode<ElemType>* right; // �񶨻ش�

	BinTreeNode(); // �޲ι��캯��
	BinTreeNode(const ElemType& val, BinTreeNode<ElemType>* l_child = NULL, BinTreeNode<ElemType>* r_child = NULL); // ���ι��캯��
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


//��������
template <class ElemType>
class BinaryTree {
protected:
	BinTreeNode<ElemType>* root; // �����
	void Destroy(BinTreeNode<ElemType>*& r); // ���������ĸ�������
public:
	BinaryTree(); // ���캯��
	BinaryTree(BinTreeNode<ElemType>* r); // ���ι��캯��
	~BinaryTree(); // ��������
	BinTreeNode<ElemType>* getRoot() const; // ���ظ����

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