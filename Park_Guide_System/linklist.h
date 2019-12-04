// 结点类与链表类
#pragma once

#include <iostream>
using namespace std;

template <class ElemType>
struct Node {
	ElemType data;
	Node<ElemType>* next;

	Node() {
		next = NULL;
	}

	Node(ElemType item, Node<ElemType>* link = NULL) {
		data = item;
		next = link;
	}
};

template <class ElemType>
class LinkList {
protected:
	Node<ElemType>* head; // 头结点指针
	mutable int cur_position; // 当前位置序号
	mutable Node<ElemType>* cur_ptr; // 当前位置指针
	int count; // 元素个数

	Node<ElemType>* getElemPtr(int position) const; // 返回指向第position个结点的指针

public:
	LinkList(); // 构造函数
	virtual ~LinkList(); // 析构函数
	int length() const; // 线性表长度
	bool isEmpty() const; // 判断线性表是否为空
	int getCurPosition() const; // 返回当前位置
	void getElem(int position, ElemType& e) const; // 返回指定位置元素到e
	void setElem(int position, const ElemType& e); // 设置指定位置为e
	void Delete(int position, ElemType& e); // 删除元素到e
	void insert(int position, const ElemType& e); // 插入元素e
};

// LinkList成员函数实现

template<class ElemType>
Node<ElemType>* LinkList<ElemType>::getElemPtr(int position) const {
	if (cur_position > position) { // 当前位置在所查找位置之后,只能从表头开始操作
		cur_position = 0;
		cur_ptr = head;
	}

	for (; cur_position < position; cur_position++) {
		cur_ptr = cur_ptr->next;
	}
	return cur_ptr;
}

// 构造函数
template<class ElemType>
LinkList<ElemType>::LinkList() {
	head = new Node<ElemType>;
	cur_ptr = head;
	cur_position = 0;
	count = 0;
}

// 析构函数
template<class ElemType>
LinkList<ElemType>::~LinkList() {
	ElemType temp;
	while (count > 0) {
		Delete(1, temp);
	}
	delete head;
}

// 线性表长度
template<class ElemType>
int LinkList<ElemType>::length() const {
	return count;
}

// 判断线性表是否为空
template<class ElemType>
bool LinkList<ElemType>::isEmpty() const {
	return head->next == NULL;
}

// 返回当前位置
template<class ElemType>
int LinkList<ElemType>::getCurPosition() const {
	return cur_position;
}

// 返回指定位置元素到e
template<class ElemType>
void LinkList<ElemType>::getElem(int position, ElemType& e) const {
	Node<ElemType>* tmp_ptr = getElemPtr(position);
	e = tmp_ptr->data;
}

// 设置指定位置为e
template<class ElemType>
void LinkList<ElemType>::setElem(int position, const ElemType& e) {
	Node<ElemType>* tmp_ptr = getElemPtr(position);
	tmp_ptr->data = e;
}

// 删除元素到e
template<class ElemType>
void LinkList<ElemType>::Delete(int position, ElemType& e) {
	Node<ElemType>* tmp_ptr = getElemPtr(position - 1);
	Node<ElemType>* next_ptr = tmp_ptr->next;
	tmp_ptr->next = next_ptr->next;
	e = next_ptr->data;

	delete next_ptr;

	if (position == length()) { // 删除尾结点,当前结点变为头结点
		cur_position = 0;
		cur_ptr = head;
	}
	else { // 删除非尾结点,当前结点变为第position个结点
		cur_position = position;
		cur_ptr = tmp_ptr->next;
	}
	count--;
}

// 插入元素e
template<class ElemType>
void LinkList<ElemType>::insert(int position, const ElemType& e) {
	Node<ElemType>* tmp_ptr = getElemPtr(position - 1);
	Node<ElemType>* new_ptr = new Node<ElemType>(e, tmp_ptr->next);
	tmp_ptr->next = new_ptr;

	cur_position = position;
	cur_ptr = new_ptr;
	count++;
}