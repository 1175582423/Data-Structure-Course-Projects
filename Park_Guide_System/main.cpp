#include "park_guide.h"

int main() {
	ifstream infile("park_info.txt");
	if (infile.fail()) { cout << "文件打开失败！" << endl; exit(-1); }
	ifstream* infile_ptr = &infile;

	ParkGuide pg(infile_ptr);
	pg.run();

	return 0;
}
