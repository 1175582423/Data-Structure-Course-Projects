// Calculator��

// ģ�����������ʵ�ֲ��ܷ��������ļ������д��ͬһ��.h�У������������Ӵ���

#pragma once

#include <iostream>
#include "stack.h"
using namespace std;

template <class ElemType>
class Calculator {
private:
	// ���ݳ�Ա
	Stack<char> operator_stack;     // ������ջ
	Stack<ElemType> operand_stack;  // ������ջ

	// ��������
	ElemType OperPrior(char op);                              // ���������ȼ�
	bool isOperator(char ch);                                 // �ж��Ƿ��ǲ�����
	void get2Operands(ElemType& left, ElemType& right);       // ��operandջ��������������
	ElemType Operate(ElemType left, char op, ElemType right); // ִ������ left op right

public:
	// Calculator() {};          // �޲ι��캯��
	// virtual ~Calculator() {}; // ����������

	void run();                  // ������ʽ
};

template <class ElemType> // ���������ȼ�
ElemType Calculator<ElemType>::OperPrior(char op)
{
	if (op == '=') return 1;
	else if (op == '(' || op == ')') return 2;
	else if (op == '+' || op == '-') return 3;
	else if (op == '*' || op == '/' || op == '%') return 4;
	else if (op == '^') return 5;
	// isOperator��ǰ�ų��˷Ƿ�����
}

template <class ElemType> // �ж��Ƿ��ǲ�����
bool Calculator<ElemType>::isOperator(char ch)
{
	if (ch == '=' || ch == '(' || ch == ')' || ch == '+' || ch == '-' ||
		ch == '*' || ch == '/' || ch == '%' || ch == '^') return true;

	return false;
}

template <class ElemType> // ��operandջ��������������
void Calculator<ElemType>::get2Operands(ElemType& left, ElemType& right) {
	this->operand_stack.Pop(right);
	this->operand_stack.Pop(left);
}

template <class ElemType> // ִ������ left op right
ElemType Calculator<ElemType>::Operate(ElemType left, char op, ElemType right) {
	if (op == '+') return (left + right);
	else if (op == '-') return (left - right);
	else if (op == '*') return (left * right);
	else if (op == '/') return (left / right);
	else if (op == '%') return (left % right);
	else if (op == '^') {
		int result = 1;
		if (right >= 0) {
			while (right != 0) {
				result *= left;
				right--;
			}
		}
		else { // right < 0
			while (right != 0) {
				result /= left;
				right++;
			}
		}
		return result;
	}
	else throw "���ʽ��������Ƿ��ַ���";
}

template <class ElemType> // ������ʽ
void Calculator<ElemType>::run() {

	char answer = 'y';

	while(answer == 'y') {
		cout << "������ʽ��" << endl;

		// ��ղ������Ͳ�����ջ����ѹ�롮=����operatorջ
		operator_stack.Clear();
		operand_stack.Clear();
		char temp_eqch = '=';
		operator_stack.Push(temp_eqch);

		char ch;
		char prior_ch; // ch��ǰһ���ַ������ǲ�������+ - * / % ^������֮Ϊ0�Ա�ʾ
		char optr_top;
		ElemType Operand;
		char Operator;

		prior_ch = '=';
		cin >> ch; // ���������ж�ȡһ���ַ� (JUST ONE CHARACTER)
		operator_stack.Top(optr_top); // �˴�Ϊ"="

		bool isrun = false; // Ϊ����ֻ����'='������

		while (optr_top != '=' || ch != '=') { // ��ǰ���ʽ��û�н��� 

			isrun = true;

			if (isdigit(ch) || ch == '.') { // chΪ�������ĵ�һ���ַ�
				cin.putback(ch); // ��ch�Ż�������
				cin >> Operand; // ��һ���������������ܲ�ֹһλ������int���ͱ���
				operand_stack.Push(Operand);
				prior_ch = '0'; // ���˵�һ�������⣬��������prior_ch��Ϊ0
				cin >> ch; // ��ȡ��һ���ַ����������궨λ��Operand����һλ
			}

			else if (!isOperator(ch)) { // ���ǲ�����Ҳ���ǲ���������Ϊ������һ�����ã��Ѿ��ų������֣�
				cout << "����ʽ�Ӻ��зǷ�����������������룡" << endl;
				exit(-1);
			}

			else { // ������
				if ((prior_ch == '=' || prior_ch == '(') && (ch == '+' || ch == '-')) { // ��Ŀ�����
					int temp0 = 0;
					operand_stack.Push(temp0);
					prior_ch = '0'; // prior_ch���ǲ��������涨Ϊ0
				}
				if ((optr_top == ')' && ch == '(') || (optr_top == '(' && ch == '=') ||
					(optr_top == '=' && ch == ')')) {
					cout << "���ʽ�﷨�������������룡" << endl;
					exit(-1);
				}
				else if (optr_top == '(' && ch == ')') { // ȥ������
					char temp_optr_top;
					operator_stack.Pop(temp_optr_top);
					//cout << "����" << temp_optr_top << endl;
					prior_ch = ')';
					cin >> ch;
				}
				else if (ch == '(' || OperPrior(optr_top) < OperPrior(ch)) { // ch���ȼ�����
					//cout << ch << "��" << optr_top << "���ȼ�����" << endl;
					operator_stack.Push(ch);
					//cout << "ѹ��" << ch << endl;
					prior_ch = ch;
					cin >> ch;
				}
				else { // ch���ȼ���С�����
					//cout << ch << "��" << optr_top << "���ȼ���С" << endl;
					operator_stack.Pop(Operator);
					//cout << "����" << Operator << endl;
					ElemType left, right;
					get2Operands(left, right);
					Operand = Operate(left, Operator, right);
					operand_stack.Push(Operand);
					//cout << "ѹ��" << Operand << endl;
				}
			}
			operator_stack.Top(optr_top);
			//cout << "�����ջ����" << optr_top << endl;
			//cout << "ch: " << ch << endl;
		}

		if (! isrun) { // ����ֻ����'='������
			ElemType temp_isnt_run = 0; operand_stack.Push(temp_isnt_run);
		}

		operand_stack.Top(Operand);
		cout << Operand << endl;

		cout << "�Ƿ����������y��n��\t";
		cin >> answer;
	}
}
