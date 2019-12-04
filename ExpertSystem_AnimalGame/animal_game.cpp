//动物游戏类的函数实现

#include "animal_game.h"
#include "stack.h"

AnimalGame::AnimalGame() { // 建立决策树
	ifstream infile("animal.txt");
	if (infile.fail()) {
		cout << "animal.txt文件打开错误！" << endl;
		exit(1);
	}
	// 后序遍历的实现 根节点在文件末尾 但是app新内容后格式混乱

	Stack<BinTreeNode<string>*> stack; // 栈中存放一个二分树的结点
	BinTreeNode<string>* center, * left, * right;
	string elem;

	while (getline(infile, elem)) { // 不读入'\n'
		int func = 1;
		bool judge = isQuestion(elem, func);
		if (judge) {
			stack.Pop(right); stack.Pop(left);
			center = new BinTreeNode<string>(elem, left, right);
			stack.Push(center);
		}
		else {
			center = new BinTreeNode<string>(elem); // 叶结点
			stack.Push(center);
		}
	}
	stack.Top(center); // 弹出栈顶指针
	DeciTree = new BinaryTree<string>(center);
	infile.close();
}

AnimalGame::~AnimalGame() {
	DeciTree->~BinaryTree();
}

void AnimalGame::Run() {
	cout << "欢迎来到动物游戏！..." << endl;
	do {
		cout << "请想一个动物，我会尽力猜到它！..." << endl;
		BinTreeNode<string>* p = DeciTree->getRoot();
		while (isQuestion(p->data)) { // 是否是问句
			bool response1 = getUserResponse();
			if (response1) { // 肯定回答
				p = p->left;
			}
			else {
				p = p->right; // 否定回答
			}
		}
		// 不是问句，到达叶结点
		bool response2 = getUserResponse();
		if (response2) { // 猜对了
			cout << "哈哈，我猜到啦！你被一台计算机打败了..." << endl;
		}
		else { // 猜错了
			cout << "你很幸运，在我还有很多不懂的时候把我难到了，我会努力学习的..." << endl;
			cout << "请教一下你想的是什么动物呢？..." << endl;
			string NewAnimal, OldAnimal = p->data, answer;
			cin >> NewAnimal;
			cout << "那么，" << NewAnimal << "区别于" << OldAnimal << "的是什么呢？..." << endl;
			cout << NewAnimal << "是：(以“的”结尾，e.g. 陆生的、有翅膀的、...)";
			cin >> answer;
			cout << "好的！我明白了..." << endl;
			p->data = answer;
			p->left = new BinTreeNode<string>(NewAnimal);
			p->right = new BinTreeNode<string>(OldAnimal);
			// 记入文件
			ofstream outfile;
			outfile.open("animal.txt", ios::out);
			if (outfile.fail()) {
				cout << "animal.txt文件打开错误！" << endl;
				exit(1);
			}
			BinTreeNode<string>* root = DeciTree->getRoot();
			memorizeInfo(root, outfile);
			outfile.close();
		}

		cout << "你还想再玩一次吗？..." << endl;
	} while (getUserResponse());

	cout << endl << "欢迎下次再来和我比试噢~" << endl;
}

void AnimalGame::memorizeInfo(BinTreeNode<string>* root, ofstream& outfile) { // 后序遍历 将决策树内容写入文件
	if (root != NULL) {
		memorizeInfo(root->left, outfile);
		memorizeInfo(root->right, outfile);
		outfile << root->data << endl; // <fstream> reloads "<<"
	}
}