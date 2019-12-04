// �������������
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
	Node<ElemType>* head; // ͷ���ָ��
	mutable int cur_position; // ��ǰλ�����
	mutable Node<ElemType>* cur_ptr; // ��ǰλ��ָ��
	int count; // Ԫ�ظ���

	Node<ElemType>* getElemPtr(int position) const; // ����ָ���position������ָ��

public:
	LinkList(); // ���캯��
	virtual ~LinkList(); // ��������
	int length() const; // ���Ա���
	bool isEmpty() const; // �ж����Ա��Ƿ�Ϊ��
	int getCurPosition() const; // ���ص�ǰλ��
	void getElem(int position, ElemType& e) const; // ����ָ��λ��Ԫ�ص�e
	void setElem(int position, const ElemType& e); // ����ָ��λ��Ϊe
	void Delete(int position, ElemType& e); // ɾ��Ԫ�ص�e
	void insert(int position, const ElemType& e); // ����Ԫ��e
};

// LinkList��Ա����ʵ��

template<class ElemType>
Node<ElemType>* LinkList<ElemType>::getElemPtr(int position) const {
	if (cur_position > position) { // ��ǰλ����������λ��֮��,ֻ�ܴӱ�ͷ��ʼ����
		cur_position = 0;
		cur_ptr = head;
	}

	for (; cur_position < position; cur_position++) {
		cur_ptr = cur_ptr->next;
	}
	return cur_ptr;
}

// ���캯��
template<class ElemType>
LinkList<ElemType>::LinkList() {
	head = new Node<ElemType>;
	cur_ptr = head;
	cur_position = 0;
	count = 0;
}

// ��������
template<class ElemType>
LinkList<ElemType>::~LinkList() {
	ElemType temp;
	while (count > 0) {
		Delete(1, temp);
	}
	delete head;
}

// ���Ա���
template<class ElemType>
int LinkList<ElemType>::length() const {
	return count;
}

// �ж����Ա��Ƿ�Ϊ��
template<class ElemType>
bool LinkList<ElemType>::isEmpty() const {
	return head->next == NULL;
}

// ���ص�ǰλ��
template<class ElemType>
int LinkList<ElemType>::getCurPosition() const {
	return cur_position;
}

// ����ָ��λ��Ԫ�ص�e
template<class ElemType>
void LinkList<ElemType>::getElem(int position, ElemType& e) const {
	Node<ElemType>* tmp_ptr = getElemPtr(position);
	e = tmp_ptr->data;
}

// ����ָ��λ��Ϊe
template<class ElemType>
void LinkList<ElemType>::setElem(int position, const ElemType& e) {
	Node<ElemType>* tmp_ptr = getElemPtr(position);
	tmp_ptr->data = e;
}

// ɾ��Ԫ�ص�e
template<class ElemType>
void LinkList<ElemType>::Delete(int position, ElemType& e) {
	Node<ElemType>* tmp_ptr = getElemPtr(position - 1);
	Node<ElemType>* next_ptr = tmp_ptr->next;
	tmp_ptr->next = next_ptr->next;
	e = next_ptr->data;

	delete next_ptr;

	if (position == length()) { // ɾ��β���,��ǰ����Ϊͷ���
		cur_position = 0;
		cur_ptr = head;
	}
	else { // ɾ����β���,��ǰ����Ϊ��position�����
		cur_position = position;
		cur_ptr = tmp_ptr->next;
	}
	count--;
}

// ����Ԫ��e
template<class ElemType>
void LinkList<ElemType>::insert(int position, const ElemType& e) {
	Node<ElemType>* tmp_ptr = getElemPtr(position - 1);
	Node<ElemType>* new_ptr = new Node<ElemType>(e, tmp_ptr->next);
	tmp_ptr->next = new_ptr;

	cur_position = position;
	cur_ptr = new_ptr;
	count++;
}