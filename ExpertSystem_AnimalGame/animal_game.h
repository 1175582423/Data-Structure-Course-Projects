//������Ϸ��

#pragma once // ����ͬһ���ļ���include���

#include "binary_tree.h"
#include "simple_utility.h"

class AnimalGame {
protected:
	BinaryTree<string>* DeciTree; // ������
	void memorizeInfo(BinTreeNode<string>* root, ofstream& outfile); // ����������¼���ļ��У�ʵ�ּ���ѧϰ�Ĺ���
public:
	AnimalGame(); // ���캯�� ��֪ʶ�ⴴ��������
	~AnimalGame(); // ��������
	void Run(); // ���к���
};