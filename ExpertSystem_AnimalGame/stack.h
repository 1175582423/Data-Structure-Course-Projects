#pragma once

// 结点与栈

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
		//一、指针的初始化阶段
		pPre = pHead;
		pCurrent = pPre->next;

		while (pCurrent)               //二、反转单链表的核心代码
		{
			pNext = pCurrent->next;   //1. 缓冲pCurrent后面的单链表
			pCurrent->next = pPre;	   //2. 反转单链表
			pPre = pCurrent;           //3.让pPre指针后移
			pCurrent = pNext;         //4. 让pCurrent指针后移
		}
		//三、处理并返回头指针
		pHead->next = NULL;                //把原头结点的next域变成空指针
		pHead = pPre;		           //把头结点指向最后一个结点产生新的头结点，也就是把原单链表的尾结点变成头结点

		return pHead;
	}
};