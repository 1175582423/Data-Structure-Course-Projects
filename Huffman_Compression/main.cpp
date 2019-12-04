#include "compression.h"

int main() {
	int choice = 0, end = 0, flag = 0; // 控制循环的变量
	Compression compression;

	cout << "欢迎使用本压缩软件！" << endl << endl;

	while (1) {
		while (flag == 0) {
			cout << endl << "请选择功能：1、压缩文件；\t\t 2、解压文件\t\t (1 或 2)："; cin >> choice;

			if (choice == 1) {
				compression.compress();
				flag = 1;
			}
			else if (choice == 2) {
				compression.decompress();
				flag = 1;
			}
			else {
				cout << endl << "请在1、2功能中选择！" << endl;
				flag = 0;
			}
		}
		
		while (flag == 1) {
			cout << endl << "是否还要继续压缩或解压文件：1、继续；\t\t 2、退出\t\t (1 或 2)："; cin >> end;

			if (end == 2) {
				cout << endl << "谢谢使用，再见！" << endl;
				flag = 0;
				return 0;
			}
			else if (end == 1) {
				cout << endl << endl;
				flag = 0;
			}
			else {
				cout << endl << "请在1、2功能中选择！" << endl;
				flag = 1;
			}
		}
	}

	return 0;
}
