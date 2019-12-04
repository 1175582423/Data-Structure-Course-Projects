// Calculator类

// 模板类的声明与实现不能放在两个文件里，必须写在同一个.h中，否则会出现链接错误！

#pragma once

#include <iostream>
#include "stack.h"
using namespace std;

template <class ElemType>
class Calculator {
private:
	// 数据成员
	Stack<char> operator_stack;     // 操作符栈
	Stack<ElemType> operand_stack;  // 操作数栈

	// 辅助函数
	ElemType OperPrior(char op);                              // 操作符优先级
	bool isOperator(char ch);                                 // 判断是否是操作符
	void get2Operands(ElemType& left, ElemType& right);       // 从operand栈弹出两个操作数
	ElemType Operate(ElemType left, char op, ElemType right); // 执行运算 left op right

public:
	// Calculator() {};          // 无参构造函数
	// virtual ~Calculator() {}; // 虚析构函数

	void run();                  // 运算表达式
};

template <class ElemType> // 操作符优先级
ElemType Calculator<ElemType>::OperPrior(char op)
{
	if (op == '=') return 1;
	else if (op == '(' || op == ')') return 2;
	else if (op == '+' || op == '-') return 3;
	else if (op == '*' || op == '/' || op == '%') return 4;
	else if (op == '^') return 5;
	// isOperator提前排除了非法输入
}

template <class ElemType> // 判断是否是操作符
bool Calculator<ElemType>::isOperator(char ch)
{
	if (ch == '=' || ch == '(' || ch == ')' || ch == '+' || ch == '-' ||
		ch == '*' || ch == '/' || ch == '%' || ch == '^') return true;

	return false;
}

template <class ElemType> // 从operand栈弹出两个操作数
void Calculator<ElemType>::get2Operands(ElemType& left, ElemType& right) {
	this->operand_stack.Pop(right);
	this->operand_stack.Pop(left);
}

template <class ElemType> // 执行运算 left op right
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
	else throw "表达式符号输入非法字符！";
}

template <class ElemType> // 运算表达式
void Calculator<ElemType>::run() {

	char answer = 'y';

	while(answer == 'y') {
		cout << "输入表达式：" << endl;

		// 清空操作数和操作符栈，并压入‘=’到operator栈
		operator_stack.Clear();
		operand_stack.Clear();
		char temp_eqch = '=';
		operator_stack.Push(temp_eqch);

		char ch;
		char prior_ch; // ch的前一个字符，若非操作符（+ - * / % ^），令之为0以表示
		char optr_top;
		ElemType Operand;
		char Operator;

		prior_ch = '=';
		cin >> ch; // 从输入流中读取一个字符 (JUST ONE CHARACTER)
		operator_stack.Top(optr_top); // 此处为"="

		bool isrun = false; // 为避免只输入'='而报错

		while (optr_top != '=' || ch != '=') { // 当前表达式还没有结束 

			isrun = true;

			if (isdigit(ch) || ch == '.') { // ch为操作数的第一个字符
				cin.putback(ch); // 将ch放回输入流
				cin >> Operand; // 将一个完整的数（可能不止一位）放入int类型变量
				operand_stack.Push(Operand);
				prior_ch = '0'; // 除了第一个数字外，其余数字prior_ch都为0
				cin >> ch; // 读取下一个字符，输入流标定位到Operand数后一位
			}

			else if (!isOperator(ch)) { // 不是操作数也不是操作符（因为经过上一个布置，已经排除了数字）
				cout << "输入式子含有非法运算符！请重新输入！" << endl;
				exit(-1);
			}

			else { // 操作符
				if ((prior_ch == '=' || prior_ch == '(') && (ch == '+' || ch == '-')) { // 单目运算符
					int temp0 = 0;
					operand_stack.Push(temp0);
					prior_ch = '0'; // prior_ch不是操作符，规定为0
				}
				if ((optr_top == ')' && ch == '(') || (optr_top == '(' && ch == '=') ||
					(optr_top == '=' && ch == ')')) {
					cout << "表达式语法有误！请重新输入！" << endl;
					exit(-1);
				}
				else if (optr_top == '(' && ch == ')') { // 去除括号
					char temp_optr_top;
					operator_stack.Pop(temp_optr_top);
					//cout << "弹出" << temp_optr_top << endl;
					prior_ch = ')';
					cin >> ch;
				}
				else if (ch == '(' || OperPrior(optr_top) < OperPrior(ch)) { // ch优先级更大
					//cout << ch << "比" << optr_top << "优先级更大" << endl;
					operator_stack.Push(ch);
					//cout << "压入" << ch << endl;
					prior_ch = ch;
					cin >> ch;
				}
				else { // ch优先级更小或等于
					//cout << ch << "比" << optr_top << "优先级更小" << endl;
					operator_stack.Pop(Operator);
					//cout << "弹出" << Operator << endl;
					ElemType left, right;
					get2Operands(left, right);
					Operand = Operate(left, Operator, right);
					operand_stack.Push(Operand);
					//cout << "压入" << Operand << endl;
				}
			}
			operator_stack.Top(optr_top);
			//cout << "运算符栈顶：" << optr_top << endl;
			//cout << "ch: " << ch << endl;
		}

		if (! isrun) { // 避免只输入'='而报错
			ElemType temp_isnt_run = 0; operand_stack.Push(temp_isnt_run);
		}

		operand_stack.Top(Operand);
		cout << Operand << endl;

		cout << "是否还想继续？（y，n）\t";
		cin >> answer;
	}
}
