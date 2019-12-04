//������Ϸ��ĺ���ʵ��

#include "animal_game.h"
#include "stack.h"

AnimalGame::AnimalGame() { // ����������
	ifstream infile("animal.txt");
	if (infile.fail()) {
		cout << "animal.txt�ļ��򿪴���" << endl;
		exit(1);
	}
	// ���������ʵ�� ���ڵ����ļ�ĩβ ����app�����ݺ��ʽ����

	Stack<BinTreeNode<string>*> stack; // ջ�д��һ���������Ľ��
	BinTreeNode<string>* center, * left, * right;
	string elem;

	while (getline(infile, elem)) { // ������'\n'
		int func = 1;
		bool judge = isQuestion(elem, func);
		if (judge) {
			stack.Pop(right); stack.Pop(left);
			center = new BinTreeNode<string>(elem, left, right);
			stack.Push(center);
		}
		else {
			center = new BinTreeNode<string>(elem); // Ҷ���
			stack.Push(center);
		}
	}
	stack.Top(center); // ����ջ��ָ��
	DeciTree = new BinaryTree<string>(center);
	infile.close();
}

AnimalGame::~AnimalGame() {
	DeciTree->~BinaryTree();
}

void AnimalGame::Run() {
	cout << "��ӭ����������Ϸ��..." << endl;
	do {
		cout << "����һ������һᾡ���µ�����..." << endl;
		BinTreeNode<string>* p = DeciTree->getRoot();
		while (isQuestion(p->data)) { // �Ƿ����ʾ�
			bool response1 = getUserResponse();
			if (response1) { // �϶��ش�
				p = p->left;
			}
			else {
				p = p->right; // �񶨻ش�
			}
		}
		// �����ʾ䣬����Ҷ���
		bool response2 = getUserResponse();
		if (response2) { // �¶���
			cout << "�������Ҳµ������㱻һ̨����������..." << endl;
		}
		else { // �´���
			cout << "������ˣ����һ��кܶ಻����ʱ������ѵ��ˣ��һ�Ŭ��ѧϰ��..." << endl;
			cout << "���һ���������ʲô�����أ�..." << endl;
			string NewAnimal, OldAnimal = p->data, answer;
			cin >> NewAnimal;
			cout << "��ô��" << NewAnimal << "������" << OldAnimal << "����ʲô�أ�..." << endl;
			cout << NewAnimal << "�ǣ�(�ԡ��ġ���β��e.g. ½���ġ��г��ġ�...)";
			cin >> answer;
			cout << "�õģ���������..." << endl;
			p->data = answer;
			p->left = new BinTreeNode<string>(NewAnimal);
			p->right = new BinTreeNode<string>(OldAnimal);
			// �����ļ�
			ofstream outfile;
			outfile.open("animal.txt", ios::out);
			if (outfile.fail()) {
				cout << "animal.txt�ļ��򿪴���" << endl;
				exit(1);
			}
			BinTreeNode<string>* root = DeciTree->getRoot();
			memorizeInfo(root, outfile);
			outfile.close();
		}

		cout << "�㻹������һ����..." << endl;
	} while (getUserResponse());

	cout << endl << "��ӭ�´��������ұ�����~" << endl;
}

void AnimalGame::memorizeInfo(BinTreeNode<string>* root, ofstream& outfile) { // ������� ������������д���ļ�
	if (root != NULL) {
		memorizeInfo(root->left, outfile);
		memorizeInfo(root->right, outfile);
		outfile << root->data << endl; // <fstream> reloads "<<"
	}
}