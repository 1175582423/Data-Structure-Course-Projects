// 公园向导类
#pragma once

#include "network.h"
#include <fstream>
#include <string>

class ParkGuide {
private:
	Network<string, double>* net_ptr; // 有公园信息建立的网
	ifstream* infile_ptr; // 输入信息的文件
	double dist[64][64]; // 顶点u, v之间最短路径长度dict[u][v]
	int path[64][64]; // 从u到v之间最短路径path[u][v]上u的后一个顶点号

	int LocateVertex(const string& e); // 返回顶点在网中的位置
	void skipOneLine(); // 跳过文件一行
	void showPath(int* p, int path_vertex_num); // 输出浏览路线
	void createPath(int ex, int v, int* p, int path_vertex_num); // 生成并输出游览路径

public:
	ParkGuide(ifstream* inf_ptr); // 构造函数
	virtual ~ParkGuide(); // 析构函数
	int run(); // 运行公园向导
};

static char getChar(istream& inStream) { // 从输入流inStream中跳过空格及制表符获取一字符
	char ch;
	while ((ch = (inStream).peek()) != EOF // peek()函数从输入流中接受1字符,流的当前位置不变
		&& ((ch = (inStream).get()) == ' ' || ch == '\t')) { // get()函数从输入流中接受1字符,流的当前位置向后移1个位置
		
		return ch;
	}
}