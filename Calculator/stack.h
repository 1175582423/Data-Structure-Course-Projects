// Node�ṹ�� & Stack��

#pragma once

template<class ElemType>
struct Node {
	ElemType data;
	Node<ElemType>* next;

	Node() { // �޲ι��캯��
		next = NULL;
	}
	Node(ElemType item, Node<ElemType>* link) { // ���ι��캯��
		data = item;
		next = link;
	}
};

template<class ElemType>
class Stack {
protected:
	Node<ElemType>* top;
public:
	Stack() { // �޲ι��캯��
		top = NULL;
	}
	~Stack() { // ��������
		Clear();
	}
	void Clear() { // ���ջ
		ElemType tmpElem;
		while (!isEmpty()) {
			Pop(tmpElem);
		}
	}
	bool isEmpty() { // �ж�ջ�Ƿ�Ϊ��
		return top == NULL;
	}
	void Pop(ElemType& e) { // ��ջ
		Node<ElemType>* old_top = top;
		e = old_top->data;
		top = old_top->next;
		delete old_top;
	}
	void Push(ElemType& e) { // ѹջ
		Node<ElemType>* new_top = new Node<ElemType>(e, top);
		top = new_top;
	}
	void Top(ElemType& e) { // ȡջ��Ԫ������
		e = top->data;
	}
};