// 哈夫曼结点（叶结点、内部节点）类、哈夫曼树类
#pragma once

#include "heap.h"
#include<iostream>
#include <string>
using namespace std;

// 哈夫曼结点类 -- 抽象基类，函数全为纯虚函数
template <class CharType, class WeightType>
class HuffmanNode {
public:
	virtual WeightType getWeight() = 0; // 返回结点的权
	virtual bool isLeaf() = 0; // 判断结点是否是叶结点
	virtual HuffmanNode<CharType, WeightType>* left() = 0; // 返回指向结点的左孩子指针
	virtual HuffmanNode<CharType, WeightType>* right() = 0; // 返回指向结点的右孩子指针
};

// 叶结点类（包含字符、权重） -- 哈夫曼结点的派生类
template <class CharType, class WeightType>
class LeafNode : public HuffmanNode<CharType, WeightType> {
private:
	CharType ch; // 叶结点包含的字符
	WeightType weight; // 叶结点的权
	// 为了析构方便：
	HuffmanNode<CharType, WeightType>* leftChild; // 左孩子
	HuffmanNode<CharType, WeightType>* rightChild; // 右孩子
public:
	LeafNode(const CharType& c, const WeightType& w); // 构造函数
	virtual ~LeafNode() {}; // 虚析构函数

	WeightType getWeight(); // 返回结点的权
	bool isLeaf(); // 判断结点是否是叶结点
	LeafNode<CharType, WeightType>* left(); // 返回指向结点的左孩子指针
	LeafNode<CharType, WeightType>* right(); // 返回指向结点的右孩子指针

	CharType getChar(); // 返回叶结点的字符
};

// 内部节点类（包含指向左右孩子的指针、权重） -- 哈夫曼结点的派生类
template <class CharType, class WeightType>
class InsideNode : public HuffmanNode<CharType, WeightType> {
private:
	WeightType weight; // 权重
	HuffmanNode<CharType, WeightType>* leftChild; // 左孩子
	HuffmanNode<CharType, WeightType>* rightChild; // 右孩子
public:
	InsideNode(const WeightType& w, HuffmanNode<CharType, WeightType>* l, HuffmanNode<CharType, WeightType>* r); // 构造函数
	virtual ~InsideNode() {}; // 虚析构函数

	WeightType getWeight(); // 返回结点的权
	bool isLeaf(); // 判断结点是否是叶结点
	HuffmanNode<CharType, WeightType>* left(); // 返回指向结点的左孩子指针
	HuffmanNode<CharType, WeightType>* right(); // 返回指向结点的右孩子指针

	void setLeft(HuffmanNode<CharType, WeightType>* child); // 设置结点的左孩子
	void setRight(HuffmanNode<CharType, WeightType>* child); // 设置结点的右孩子
};

// 哈夫曼树类
template <class CharType, class WeightType>
class HuffmanTree {
protected:
	HuffmanNode<CharType, WeightType>* root; // 根
	string* char_codes; // 字符编码信息
	HuffmanNode<CharType, WeightType>* pCurNode; // 译码时从根节点到叶结点路径的当前节点
	int num; // 叶结点的个数

	void createCode(HuffmanNode<CharType, WeightType>* r, char char_code[], int len = 0); // 生成字符编码
	void clear(HuffmanNode<CharType, WeightType>* r); // 清除以r为根的二叉树
	
public:
	HuffmanTree(CharType ch[], WeightType w[], int n); // 构造函数
	virtual ~HuffmanTree(); // 析构函数
	string encode(CharType ch); // 编码
	string decode(string code); // 译码
};


// 叶结点类函数的实现

// 构造函数
template<class CharType, class WeightType>
LeafNode<CharType, WeightType>::LeafNode(const CharType& c, const WeightType& w) {
	ch = c;
	weight = w;
	leftChild = NULL;
	rightChild = NULL;
}

// 取结点字符
template <class CharType, class WeightType>
CharType LeafNode<CharType, WeightType>::getChar() {
	return ch;
}

// 取结点权重
template <class CharType, class WeightType>
WeightType LeafNode<CharType, WeightType>::getWeight() {
	return weight;
}

// 判断是否是叶结点
template <class CharType, class WeightType>
bool LeafNode<CharType, WeightType>::isLeaf() {
	return true;
}

// 返回左孩子
template <class CharType, class WeightType>
LeafNode<CharType, WeightType>* LeafNode<CharType, WeightType>::left() {
	return NULL;
}

// 返回右孩子
template <class CharType, class WeightType>
LeafNode<CharType, WeightType>* LeafNode<CharType, WeightType>::right() {
	return NULL;
}


// 内部节点类函数的实现

// 构造函数
template <class CharType, class WeightType>
InsideNode<CharType, WeightType>::InsideNode(const WeightType& w, HuffmanNode<CharType, WeightType>* l, HuffmanNode<CharType, WeightType>* r) {
	weight = w;
	leftChild = l;
	rightChild = r;
}

// 取结点权重
template <class CharType, class WeightType>
WeightType InsideNode<CharType, WeightType>::getWeight() {
	return weight;
}

// 判断是否是叶结点
template <class CharType, class WeightType>
bool InsideNode<CharType, WeightType>::isLeaf() {
	return false;
}

// 返回左孩子
template <class CharType, class WeightType>
HuffmanNode<CharType, WeightType>* InsideNode<CharType, WeightType>::left() {
	return leftChild;
}

// 返回右孩子
template <class CharType, class WeightType>
HuffmanNode<CharType, WeightType>* InsideNode<CharType, WeightType>::right() {
	return rightChild;
}

// 设置结点的左孩子
template <class CharType, class WeightType>
void InsideNode<CharType, WeightType>::setLeft(HuffmanNode<CharType, WeightType>* child) {
	leftChild = child;
}

// 设置结点的右孩子
template <class CharType, class WeightType>
void InsideNode<CharType, WeightType>::setRight(HuffmanNode<CharType, WeightType>* child) {
	rightChild = child;
}


// 帮助函数
// 生成Huffman树时，要选择根节点权重最小的两棵二叉树，此处采用小顶堆方式存储二叉树的根，则又需要比较两二叉树大小，所有重载比较符号
// 而重载运算符中操作数应包含非基本类型，即不能全是指针类型，否则报错（xxx must have an argument of class or enumerated type）
// 所以创建一个结构体，其成员是指向HuffmanNode二叉树的指针

// 辅助结构体
template <class CharType, class WeightType>
struct NodeHelp {
	HuffmanNode<CharType, WeightType>* ptr;

	NodeHelp() {
		ptr = NULL;
	}
};

// 重载运算符（heap.h用到的运算符）
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


// 哈夫曼树类函数的实现

// 辅助函数 -- 生成字符编码
template <class CharType, class WeightType>
void HuffmanTree<CharType, WeightType>::createCode(HuffmanNode<CharType, WeightType>* r, char char_code[], int len) {
	if (r->isLeaf()) { // 叶结点
		CharType ch = ((LeafNode<CharType, WeightType>*) r)->getChar(); // 转换为叶结点类型
		char_code[len] = '\0'; // 结束符
		char_codes[(unsigned int)(ch)] = (string)char_code;
		// cout << "叶结点..." << ch << ": " << char_codes[(unsigned int)(ch)] << endl;
	}
	else { // 内部节点
		// 递归结束后，不改变len，所以每一层char_code[]内容会被覆盖

		// cout << "左分支..." << endl;
		char_code[len] = '0'; // 左分支编码'0'
		createCode(r->left(), char_code, len + 1); // 向左边搜索

		// cout << "右分支..." << endl;
		char_code[len] = '1'; // 右分支编码'1'
		createCode(r->right(), char_code, len + 1); // 向右边搜索
	}
}

// 辅助函数 -- 清除以r为根的二叉树
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
	// cout << "clear()完成..." << endl;
}

// 构造函数
template <class CharType, class WeightType>
HuffmanTree<CharType, WeightType>::HuffmanTree(CharType ch[], WeightType w[], int n) {
	// cout << "开始创建哈夫曼树..." << endl;
	int N = n; // ch[], w[]数组的大小
	Heap<NodeHelp<CharType, WeightType>> heap(N); // 小顶堆，最多有N个元素
	char_codes = new string[N];

	//生成森林
	for (int i = 0; i < N; i++) {
		if (w[i] != 0) {
			NodeHelp<CharType, WeightType> help_node;
			help_node.ptr = new LeafNode<CharType, WeightType>(ch[i], w[i]);
			heap.inQueue(help_node); // 森林中每棵树只有一个结点
			// cout << ch[i] << ": " << w[i] << "入队..." << endl;
		}
	}
	// cout << "成功生成森林..." << endl;

	num = heap.getCount(); // 叶结点的

	// 建立Huffman树
	for (int i = 0; i < num - 1; i++) {
		NodeHelp<CharType, WeightType> r, r1, r2;
		heap.outQueue(r1);
		heap.outQueue(r2);
		r.ptr = new InsideNode<CharType, WeightType>(r1.ptr->getWeight() + r2.ptr->getWeight(), r1.ptr, r2.ptr);
		heap.inQueue(r);
		// cout << "中间结点：" << r1.ptr->getWeight() + r2.ptr->getWeight() << "入队..."<< endl;
	}
	// cout << "成功生成树..." << endl;

	NodeHelp<CharType, WeightType> rt; // 临时
	heap.outQueue(rt);
	// cout << "小顶堆堆顶出队..." << endl;

	// 设置成员变量
	root = rt.ptr; // 即为Huffman树
	pCurNode = root; // 初始化为root
	// cout << "root、pCurNode初始化完成..." << endl;
	char* char_code = new char[N];
	// cout << "createCode()调用..." << endl;
	createCode(root, char_code); // 设置char_codes
	// cout << "哈夫曼树生成成功..." << endl;
}

// 析构函数
template <class CharType, class WeightType>
HuffmanTree<CharType, WeightType>::~HuffmanTree() {
	clear(root);
	// cout << "析构HuffmanTree完成..." << endl;
}

// 译码
template <class CharType, class WeightType>
string HuffmanTree<CharType, WeightType>::encode(CharType ch) {
	return char_codes[(unsigned int)(ch)];
}

// 编码
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