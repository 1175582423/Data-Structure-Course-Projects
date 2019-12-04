#pragma once

// �����ջ

template<class ElemType>
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

template<class ElemType>
class Stack {
protected:
	Node<ElemType>* top = NULL;
public:
	void Pop(ElemType& e) {
		Node<ElemType>* old_top = top;
		e = old_top->data;
		top = old_top->next;
		delete old_top;
	}
	void Push(ElemType& e) {
		Node<ElemType>* new_top = new Node<ElemType>(e, top);
		top = new_top;
	}
	void Top(ElemType& e) const {
		e = top->data;
	}
	Node<ElemType>* reverseStack(Node<ElemType>* pHead) {
		if (pHead == NULL)
			return NULL;
		Node<ElemType> * pCurrent, *pPre, *pNext;
		//һ��ָ��ĳ�ʼ���׶�
		pPre = pHead;
		pCurrent = pPre->next;

		while (pCurrent)               //������ת������ĺ��Ĵ���
		{
			pNext = pCurrent->next;   //1. ����pCurrent����ĵ�����
			pCurrent->next = pPre;	   //2. ��ת������
			pPre = pCurrent;           //3.��pPreָ�����
			pCurrent = pNext;         //4. ��pCurrentָ�����
		}
		//������������ͷָ��
		pHead->next = NULL;                //��ԭͷ����next���ɿ�ָ��
		pHead = pPre;		           //��ͷ���ָ�����һ���������µ�ͷ��㣬Ҳ���ǰ�ԭ�������β�����ͷ���

		return pHead;
	}
};