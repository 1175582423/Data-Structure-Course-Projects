// ���ܺ�����ʵ��

#pragma once // ����ͬһ���ļ���include���

#include <iostream>
#include <string>
#include <fstream> // ��ostream����<<
using namespace std;

// ��main.cpp & animal_game.cpp ��������"animal_game.h"->"unitility.h"�����º�����������������

static bool getUserResponse() {
	char ch; // �û��ش��ַ�
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
			cout << "����y(es)��n(o)�ش�" << endl;
		}
	}
}

// ���ݹؼ������ɾ��ӣ����ж������⻹�Ǵ�
// func == 0 ������ӣ�func != 0 ���������
static bool isQuestion(string item, int func = 0) {
	if (func == 0) {
		string str1 = "����Ķ�����", str2 = "��	��ش�";
		string sentence = str1 + item + str2;
		cout << sentence; // �������
	}
	if (item.substr(item.length() - 2, 2) == "��") { // ���һ�����Ƿ��ǡ��ġ�->�жϳ��Ƿ����ʾ�
		return true;
	}
	else {
		return false;
	}
}