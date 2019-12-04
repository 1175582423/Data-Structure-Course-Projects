// ParkGuide类成员函数实现

#include "park_guide.h"

// 返回顶点在网中的位置
int ParkGuide::LocateVertex(const string& v) {
	int v_n = net_ptr->getVertexNum();
	Vertex<string, double>* table = net_ptr->getVertexTable();
	for (int i = 0; i < v_n; i++) {
		if (v == table[i].data) {
			//cout << "找到顶点编号: " << i << endl;
			return i;
		}
	}
	return -1; // 没找到
}

// 跳过文件一行
void ParkGuide::skipOneLine() {
	char tmp[256];
	(*infile_ptr).getline(tmp, 256);
}

// 输出浏览路线
void ParkGuide::showPath(int* p, int path_vertex_num) {
	int i = 1;
	Vertex<string, double>* table = net_ptr->getVertexTable();
	double len = dist[p[0]][p[1]];
	cout << "游览路径：" << table[p[0]].data;
	for (i = 1; i < path_vertex_num - 1; i++) {
		len += dist[p[i]][p[i + 1]];
		cout << "->" << table[p[i]].data;
	}
	cout << "->" << table[p[i]].data << endl;
	cout << "路径长度：" << len << " 米" << endl;
}

// 生成并输出游览路径
// ex为出口，v为当前顶点，p[]为游览路径，path_vertex_num为当前路径顶点数
void ParkGuide::createPath(int ex, int v, int* p, int path_vertex_num) {
	for (int w = net_ptr->FirstAdjVex(v); w >= 0; w = net_ptr->NextAdjVex(v, w)) {
		if (path_vertex_num == net_ptr->getVertexNum()) {
			//cout << "输出路径" << endl;
			showPath(p, path_vertex_num);
		}
		else if (net_ptr->getTag(w) == false) {
			//cout << "添加结点" << endl;
			p[path_vertex_num++] = w;
			net_ptr->setTag(w, true);
			//cout << "换一个起点" << endl;
			createPath(ex, w, p, path_vertex_num);

			//cout << "回溯" << endl;
			path_vertex_num--;
			net_ptr->setTag(w, false);
		}
	}
}


// 构造函数
ParkGuide::ParkGuide(ifstream* inf_ptr) {
	//cout << "开始创建ParkGuide对象..." << endl;

	infile_ptr = inf_ptr;
	char ch;

	// 从输入流中输入景点数，在"n="后面
	(*infile_ptr).seekg(0); // 定位到文件开始处
	ch = getChar(*infile_ptr);
	while (ch != 'n') { // 查找以"n"开始的行
		if (ch != '\n') skipOneLine();

		ch = getChar(*infile_ptr);
	}
	getChar(*infile_ptr); // 跳过"="

	int n; *infile_ptr >> n;
	//cout << "读入n完成..." << "n = " << n << endl;

	string* v = new string[n + 2]; // 网的定点元素，包括出口入口

	// 输入景点名称，景点名称在"v="后面，名称中不带空格，景点间以空格分隔
	(*infile_ptr).seekg(0); // 定位到文件开始处
	ch = getChar(*infile_ptr);
	while (ch != 'v') { // 查找以"v"开始的行
		if (ch != '\n') skipOneLine();

		ch = getChar(*infile_ptr);
	}
	getChar(*infile_ptr); // 跳过"="

	for (int i = 0; i < n; i++) { // 读入景点名称
		*infile_ptr >> v[i];
	}
	v[n] = "入口"; v[n + 1] = "出口";
	//cout << "读入v完成..." << "例如：v[0] = " << v[0] << endl;

	/*
	// 输入最多显示路线条数，在"s="后面
	(*infile_ptr).seekg(0); // 定位到文件开始处
	ch = getChar(*infile_ptr);
	while (ch != 's') { // 查找以"s"开始的行
		if (ch != '\n') skipOneLine();

		ch = getChar(*infile_ptr);
	}
	getChar(*infile_ptr); // 跳过"="
	*infile_ptr >> path_max_num;
	//cout << "读入s完成..." << "s = " << path_max_num << endl;
	*/

	net_ptr = new Network<string, double>(v, n + 2);
	//cout << "建立Network完成..." << endl;

	delete[] v;

	// 输入边信息
	(*infile_ptr).seekg(0); // 定位到文件开始处
	ch = getChar(*infile_ptr);
	while (true) {
		while (ch != '(' && ch != EOF) { // 查找以'('开始的行，或者文件结束
			if (ch != '\n') skipOneLine();
			ch = getChar(*infile_ptr);
		}
		//cout << "找到\"(\"..." << endl;

		if (ch == EOF) break;

		string e1, e2;
		int v1, v2;
		double w;
		(*infile_ptr) >> e1 >> e2 >> w;
		//cout << "读入顶点信息与边权重：" << e1 << "->" << e2 << ": " << w << "米" << endl;

		v1 = LocateVertex(e1); v2 = LocateVertex(e2);
		if (v1 == -1 || v2 == -1) { cout << "边顶点元素错误！" << endl; exit(-1); }
		net_ptr->insertEdge(v1, v2, w);
		//cout << "插入边" << e1 << "->" << e2 << ": " << w << endl;

		ch = getChar(*infile_ptr);
	}
	//cout << "读入边信息完成..." << endl;

	// 初始化dist[][] path[][]
	//cout << "初始化dist[][] path[][]" << endl;
	for (int u = 0; u < net_ptr->getVertexNum(); u++) {
		for (int v = 0; v < net_ptr->getVertexNum(); v++) {
			dist[u][v] = (u != v) ? net_ptr->getWeight(u, v) : 0;
			if (u != v && dist[u][v] < net_ptr->getInfinity()) path[u][v] = v; // 存在<u, v>
			else path[u][v] = -1;
		}
	}
	// Floyd算法求图各队顶点最短路径
	//cout << "Floyd算法求图各队顶点最短路径" << endl;
	for (int k = 0; k < net_ptr->getVertexNum(); k++) {
		for (int i = 0; i < net_ptr->getVertexNum(); i++) {
			for (int j = 0; j < net_ptr->getVertexNum(); j++) {
				if (dist[i][j] > (dist[i][k] + dist[k][j])) {
					// i->k->j 比 i->j 更短
					dist[i][j] = dist[i][k] + dist[k][j];
					path[i][j] = path[i][k];
				}
			}
		}
	}
}

// 析构函数
ParkGuide::~ParkGuide() {
	net_ptr->~Network();
}

// 运行公园向导
int ParkGuide::run() {
	cout << "欢迎使用公园向导系统！" << endl;
	int choice = 0;
	while (true) {
		cout << endl << "请选择功能：" << endl;
		cout << "1. 根据起点与终点显示最短路径" << endl;
		cout << "2. 显示能不重复而又能游览所有景点的公园路线（若无输出，代表不存在能经过所有顶点仅一次的路径）" << endl;
		cout << "3. 退出" << endl;
		cout << "(1 或 2 或 3)："; cin >> choice;

		if (choice == 1) {
			string e1, e2;
			cout << "起点："; cin >> e1;
			cout << "终点："; cin >> e2;

			int v1 = LocateVertex(e1), v2 = LocateVertex(e2), k = path[v1][v2];
			Vertex<string, double>* table = net_ptr->getVertexTable();

			cout << "最短路线：" << table[v1].data << "->";

			while (k != v2) {
				cout << table[k].data << "->";
				k = path[k][v2];
			}
			cout << table[v2].data << endl;

			cout << "路线距离：" << dist[v1][v2] << "米" << endl;
		}

		else if (choice == 2) {
			int ex = LocateVertex("出口"), in = LocateVertex("入口"), p[64], n = 1;
			p[0] = in;

			//cout << "开始寻找简单路径" << endl;
			createPath(ex, in, p, n);
		}

		else if (choice == 3) {
			cout << endl << "谢谢使用！" << endl;
			return 0;
		}

		else {
			cout << endl << "请输入1或2或3，不能输入其他字符！" << endl;
		}
	}
}
