// 主函数

#include <iostream>
#include "calculator.h"
using namespace std;

int main() {
	char answer = 'y';
	Calculator<int> c;
	c.run();
	
	cout << endl << "谢谢使用！" << endl;

	return 0;
}
