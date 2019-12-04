//动物游戏类

#pragma once // 避免同一个文件被include多次

#include "binary_tree.h"
#include "simple_utility.h"

class AnimalGame {
protected:
	BinaryTree<string>* DeciTree; // 决策树
	void memorizeInfo(BinTreeNode<string>* root, ofstream& outfile); // 将决策树记录到文件中，实现记忆学习的功能
public:
	AnimalGame(); // 构造函数 由知识库创建决策树
	~AnimalGame(); // 析构函数
	void Run(); // 运行函数
};