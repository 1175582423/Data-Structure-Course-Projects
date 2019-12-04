// Node结构体 & Stack类

#pragma once

template<class ElemType>
struct Node {
	ElemType data;
	Node<ElemType>* next;

	Node() { // 无参构造函数
		next = NULL;
	}
	Node(ElemType item, Node<ElemType>* link) { // 含参构造函数
		data = item;
		next = link;
	}
};

template<class ElemType>
class Stack {
protected:
	Node<ElemType>* top;
public:
	Stack() { // 无参构造函数
		top = NULL;
	}
	~Stack() { // 析构函数
		Clear();
	}
	void Clear() { // 清空栈
		ElemType tmpElem;
		while (!isEmpty()) {
			Pop(tmpElem);
		}
	}
	bool isEmpty() { // 判断栈是否为空
		return top == NULL;
	}
	void Pop(ElemType& e) { // 弹栈
		Node<ElemType>* old_top = top;
		e = old_top->data;
		top = old_top->next;
		delete old_top;
	}
	void Push(ElemType& e) { // 压栈
		Node<ElemType>* new_top = new Node<ElemType>(e, top);
		top = new_top;
	}
	void Top(ElemType& e) { // 取栈顶元素数据
		e = top->data;
	}
};