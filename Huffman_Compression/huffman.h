// ��������㣨Ҷ��㡢�ڲ��ڵ㣩�ࡢ����������
#pragma once

#include "heap.h"
#include<iostream>
#include <string>
using namespace std;

// ����������� -- ������࣬����ȫΪ���麯��
template <class CharType, class WeightType>
class HuffmanNode {
public:
	virtual WeightType getWeight() = 0; // ���ؽ���Ȩ
	virtual bool isLeaf() = 0; // �жϽ���Ƿ���Ҷ���
	virtual HuffmanNode<CharType, WeightType>* left() = 0; // ����ָ���������ָ��
	virtual HuffmanNode<CharType, WeightType>* right() = 0; // ����ָ������Һ���ָ��
};

// Ҷ����ࣨ�����ַ���Ȩ�أ� -- ����������������
template <class CharType, class WeightType>
class LeafNode : public HuffmanNode<CharType, WeightType> {
private:
	CharType ch; // Ҷ���������ַ�
	WeightType weight; // Ҷ����Ȩ
	// Ϊ���������㣺
	HuffmanNode<CharType, WeightType>* leftChild; // ����
	HuffmanNode<CharType, WeightType>* rightChild; // �Һ���
public:
	LeafNode(const CharType& c, const WeightType& w); // ���캯��
	virtual ~LeafNode() {}; // ����������

	WeightType getWeight(); // ���ؽ���Ȩ
	bool isLeaf(); // �жϽ���Ƿ���Ҷ���
	LeafNode<CharType, WeightType>* left(); // ����ָ���������ָ��
	LeafNode<CharType, WeightType>* right(); // ����ָ������Һ���ָ��

	CharType getChar(); // ����Ҷ�����ַ�
};

// �ڲ��ڵ��ࣨ����ָ�����Һ��ӵ�ָ�롢Ȩ�أ� -- ����������������
template <class CharType, class WeightType>
class InsideNode : public HuffmanNode<CharType, WeightType> {
private:
	WeightType weight; // Ȩ��
	HuffmanNode<CharType, WeightType>* leftChild; // ����
	HuffmanNode<CharType, WeightType>* rightChild; // �Һ���
public:
	InsideNode(const WeightType& w, HuffmanNode<CharType, WeightType>* l, HuffmanNode<CharType, WeightType>* r); // ���캯��
	virtual ~InsideNode() {}; // ����������

	WeightType getWeight(); // ���ؽ���Ȩ
	bool isLeaf(); // �жϽ���Ƿ���Ҷ���
	HuffmanNode<CharType, WeightType>* left(); // ����ָ���������ָ��
	HuffmanNode<CharType, WeightType>* right(); // ����ָ������Һ���ָ��

	void setLeft(HuffmanNode<CharType, WeightType>* child); // ���ý�������
	void setRight(HuffmanNode<CharType, WeightType>* child); // ���ý����Һ���
};

// ����������
template <class CharType, class WeightType>
class HuffmanTree {
protected:
	HuffmanNode<CharType, WeightType>* root; // ��
	string* char_codes; // �ַ�������Ϣ
	HuffmanNode<CharType, WeightType>* pCurNode; // ����ʱ�Ӹ��ڵ㵽Ҷ���·���ĵ�ǰ�ڵ�
	int num; // Ҷ���ĸ���

	void createCode(HuffmanNode<CharType, WeightType>* r, char char_code[], int len = 0); // �����ַ�����
	void clear(HuffmanNode<CharType, WeightType>* r); // �����rΪ���Ķ�����
	
public:
	HuffmanTree(CharType ch[], WeightType w[], int n); // ���캯��
	virtual ~HuffmanTree(); // ��������
	string encode(CharType ch); // ����
	string decode(string code); // ����
};


// Ҷ����ຯ����ʵ��

// ���캯��
template<class CharType, class WeightType>
LeafNode<CharType, WeightType>::LeafNode(const CharType& c, const WeightType& w) {
	ch = c;
	weight = w;
	leftChild = NULL;
	rightChild = NULL;
}

// ȡ����ַ�
template <class CharType, class WeightType>
CharType LeafNode<CharType, WeightType>::getChar() {
	return ch;
}

// ȡ���Ȩ��
template <class CharType, class WeightType>
WeightType LeafNode<CharType, WeightType>::getWeight() {
	return weight;
}

// �ж��Ƿ���Ҷ���
template <class CharType, class WeightType>
bool LeafNode<CharType, WeightType>::isLeaf() {
	return true;
}

// ��������
template <class CharType, class WeightType>
LeafNode<CharType, WeightType>* LeafNode<CharType, WeightType>::left() {
	return NULL;
}

// �����Һ���
template <class CharType, class WeightType>
LeafNode<CharType, WeightType>* LeafNode<CharType, WeightType>::right() {
	return NULL;
}


// �ڲ��ڵ��ຯ����ʵ��

// ���캯��
template <class CharType, class WeightType>
InsideNode<CharType, WeightType>::InsideNode(const WeightType& w, HuffmanNode<CharType, WeightType>* l, HuffmanNode<CharType, WeightType>* r) {
	weight = w;
	leftChild = l;
	rightChild = r;
}

// ȡ���Ȩ��
template <class CharType, class WeightType>
WeightType InsideNode<CharType, WeightType>::getWeight() {
	return weight;
}

// �ж��Ƿ���Ҷ���
template <class CharType, class WeightType>
bool InsideNode<CharType, WeightType>::isLeaf() {
	return false;
}

// ��������
template <class CharType, class WeightType>
HuffmanNode<CharType, WeightType>* InsideNode<CharType, WeightType>::left() {
	return leftChild;
}

// �����Һ���
template <class CharType, class WeightType>
HuffmanNode<CharType, WeightType>* InsideNode<CharType, WeightType>::right() {
	return rightChild;
}

// ���ý�������
template <class CharType, class WeightType>
void InsideNode<CharType, WeightType>::setLeft(HuffmanNode<CharType, WeightType>* child) {
	leftChild = child;
}

// ���ý����Һ���
template <class CharType, class WeightType>
void InsideNode<CharType, WeightType>::setRight(HuffmanNode<CharType, WeightType>* child) {
	rightChild = child;
}


// ��������
// ����Huffman��ʱ��Ҫѡ����ڵ�Ȩ����С�����ö��������˴�����С���ѷ�ʽ�洢�������ĸ���������Ҫ�Ƚ�����������С���������رȽϷ���
// ������������в�����Ӧ�����ǻ������ͣ�������ȫ��ָ�����ͣ����򱨴�xxx must have an argument of class or enumerated type��
// ���Դ���һ���ṹ�壬���Ա��ָ��HuffmanNode��������ָ��

// �����ṹ��
template <class CharType, class WeightType>
struct NodeHelp {
	HuffmanNode<CharType, WeightType>* ptr;

	NodeHelp() {
		ptr = NULL;
	}
};

// �����������heap.h�õ����������
template <class CharType, class WeightType>
bool operator< (const NodeHelp<CharType, WeightType>& first, const NodeHelp<CharType, WeightType>& second) {
	return first.ptr->getWeight() < second.ptr->getWeight();
}

template <class CharType, class WeightType>
bool operator> (const NodeHelp<CharType, WeightType>& first, const NodeHelp<CharType, WeightType>& second) {
	return first.ptr->getWeight() > second.ptr->getWeight();
}

template <class CharType, class WeightType>
bool operator<= (const NodeHelp<CharType, WeightType>& first, const NodeHelp<CharType, WeightType>& second) {
	return first.ptr->getWeight() <= second.ptr->getWeight();
}


// ���������ຯ����ʵ��

// �������� -- �����ַ�����
template <class CharType, class WeightType>
void HuffmanTree<CharType, WeightType>::createCode(HuffmanNode<CharType, WeightType>* r, char char_code[], int len) {
	if (r->isLeaf()) { // Ҷ���
		CharType ch = ((LeafNode<CharType, WeightType>*) r)->getChar(); // ת��ΪҶ�������
		char_code[len] = '\0'; // ������
		char_codes[(unsigned int)(ch)] = (string)char_code;
		// cout << "Ҷ���..." << ch << ": " << char_codes[(unsigned int)(ch)] << endl;
	}
	else { // �ڲ��ڵ�
		// �ݹ�����󣬲��ı�len������ÿһ��char_code[]���ݻᱻ����

		// cout << "���֧..." << endl;
		char_code[len] = '0'; // ���֧����'0'
		createCode(r->left(), char_code, len + 1); // ���������

		// cout << "�ҷ�֧..." << endl;
		char_code[len] = '1'; // �ҷ�֧����'1'
		createCode(r->right(), char_code, len + 1); // ���ұ�����
	}
}

// �������� -- �����rΪ���Ķ�����
template <class CharType, class WeightType>
void HuffmanTree<CharType, WeightType>::clear(HuffmanNode<CharType, WeightType>* r) {
	if (r) {
		HuffmanNode<CharType, WeightType>* L = r->left();
		HuffmanNode<CharType, WeightType>* R = r->right();
		delete r;
		if (L) {
			clear(L);
		}
		if (R) {
			clear(R);
		}
	}
	// cout << "clear()���..." << endl;
}

// ���캯��
template <class CharType, class WeightType>
HuffmanTree<CharType, WeightType>::HuffmanTree(CharType ch[], WeightType w[], int n) {
	// cout << "��ʼ������������..." << endl;
	int N = n; // ch[], w[]����Ĵ�С
	Heap<NodeHelp<CharType, WeightType>> heap(N); // С���ѣ������N��Ԫ��
	char_codes = new string[N];

	//����ɭ��
	for (int i = 0; i < N; i++) {
		if (w[i] != 0) {
			NodeHelp<CharType, WeightType> help_node;
			help_node.ptr = new LeafNode<CharType, WeightType>(ch[i], w[i]);
			heap.inQueue(help_node); // ɭ����ÿ����ֻ��һ�����
			// cout << ch[i] << ": " << w[i] << "���..." << endl;
		}
	}
	// cout << "�ɹ�����ɭ��..." << endl;

	num = heap.getCount(); // Ҷ����

	// ����Huffman��
	for (int i = 0; i < num - 1; i++) {
		NodeHelp<CharType, WeightType> r, r1, r2;
		heap.outQueue(r1);
		heap.outQueue(r2);
		r.ptr = new InsideNode<CharType, WeightType>(r1.ptr->getWeight() + r2.ptr->getWeight(), r1.ptr, r2.ptr);
		heap.inQueue(r);
		// cout << "�м��㣺" << r1.ptr->getWeight() + r2.ptr->getWeight() << "���..."<< endl;
	}
	// cout << "�ɹ�������..." << endl;

	NodeHelp<CharType, WeightType> rt; // ��ʱ
	heap.outQueue(rt);
	// cout << "С���ѶѶ�����..." << endl;

	// ���ó�Ա����
	root = rt.ptr; // ��ΪHuffman��
	pCurNode = root; // ��ʼ��Ϊroot
	// cout << "root��pCurNode��ʼ�����..." << endl;
	char* char_code = new char[N];
	// cout << "createCode()����..." << endl;
	createCode(root, char_code); // ����char_codes
	// cout << "�����������ɳɹ�..." << endl;
}

// ��������
template <class CharType, class WeightType>
HuffmanTree<CharType, WeightType>::~HuffmanTree() {
	clear(root);
	// cout << "����HuffmanTree���..." << endl;
}

// ����
template <class CharType, class WeightType>
string HuffmanTree<CharType, WeightType>::encode(CharType ch) {
	return char_codes[(unsigned int)(ch)];
}

// ����
template <class CharType, class WeightType>
string HuffmanTree<CharType, WeightType>::decode(string code) {
	string char_list;
	for (unsigned int pos = 0; pos < (code.length()); pos++) {
		if (code[pos] == '0') {
			pCurNode = pCurNode->left();
		}
		else {
			pCurNode = pCurNode->right();
		}
		if (pCurNode->isLeaf()) {
			char_list += ((LeafNode<CharType, WeightType>*)pCurNode)->getChar();
			pCurNode = root;
		}
	}
	return char_list;
}