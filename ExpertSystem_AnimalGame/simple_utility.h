// 功能函数的实现

#pragma once // 避免同一个文件被include多次

#include <iostream>
#include <string>
#include <fstream> // 对ostream重载<<
using namespace std;

// 若main.cpp & animal_game.cpp 都包含了"animal_game.h"->"unitility.h"，导致函数被定义声明两次

static bool getUserResponse() {
	char ch; // 用户回答字符
	while (true) {
		cout << "(y, n) ? : ";
		cin >> ch;
		if (ch == 'y') {
			return true;
		}
		else if (ch == 'n') {
			return false;
		}
		else {
			cout << "请用y(es)或n(o)回答！" << endl;
		}
	}
}

// 根据关键词生成句子，并判断是问题还是答案
// func == 0 输出句子；func != 0 不输出句子
static bool isQuestion(string item, int func = 0) {
	if (func == 0) {
		string str1 = "你想的动物是", str2 = "吗？	请回答";
		string sentence = str1 + item + str2;
		cout << sentence; // 输出句子
	}
	if (item.substr(item.length() - 2, 2) == "的") { // 最后一个字是否是“的”->判断出是否是问句
		return true;
	}
	else {
		return false;
	}
}