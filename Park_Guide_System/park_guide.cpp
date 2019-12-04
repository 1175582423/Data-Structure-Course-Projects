// ParkGuide���Ա����ʵ��

#include "park_guide.h"

// ���ض��������е�λ��
int ParkGuide::LocateVertex(const string& v) {
	int v_n = net_ptr->getVertexNum();
	Vertex<string, double>* table = net_ptr->getVertexTable();
	for (int i = 0; i < v_n; i++) {
		if (v == table[i].data) {
			//cout << "�ҵ�������: " << i << endl;
			return i;
		}
	}
	return -1; // û�ҵ�
}

// �����ļ�һ��
void ParkGuide::skipOneLine() {
	char tmp[256];
	(*infile_ptr).getline(tmp, 256);
}

// ������·��
void ParkGuide::showPath(int* p, int path_vertex_num) {
	int i = 1;
	Vertex<string, double>* table = net_ptr->getVertexTable();
	double len = dist[p[0]][p[1]];
	cout << "����·����" << table[p[0]].data;
	for (i = 1; i < path_vertex_num - 1; i++) {
		len += dist[p[i]][p[i + 1]];
		cout << "->" << table[p[i]].data;
	}
	cout << "->" << table[p[i]].data << endl;
	cout << "·�����ȣ�" << len << " ��" << endl;
}

// ���ɲ��������·��
// exΪ���ڣ�vΪ��ǰ���㣬p[]Ϊ����·����path_vertex_numΪ��ǰ·��������
void ParkGuide::createPath(int ex, int v, int* p, int path_vertex_num) {
	for (int w = net_ptr->FirstAdjVex(v); w >= 0; w = net_ptr->NextAdjVex(v, w)) {
		if (path_vertex_num == net_ptr->getVertexNum()) {
			//cout << "���·��" << endl;
			showPath(p, path_vertex_num);
		}
		else if (net_ptr->getTag(w) == false) {
			//cout << "��ӽ��" << endl;
			p[path_vertex_num++] = w;
			net_ptr->setTag(w, true);
			//cout << "��һ�����" << endl;
			createPath(ex, w, p, path_vertex_num);

			//cout << "����" << endl;
			path_vertex_num--;
			net_ptr->setTag(w, false);
		}
	}
}


// ���캯��
ParkGuide::ParkGuide(ifstream* inf_ptr) {
	//cout << "��ʼ����ParkGuide����..." << endl;

	infile_ptr = inf_ptr;
	char ch;

	// �������������뾰��������"n="����
	(*infile_ptr).seekg(0); // ��λ���ļ���ʼ��
	ch = getChar(*infile_ptr);
	while (ch != 'n') { // ������"n"��ʼ����
		if (ch != '\n') skipOneLine();

		ch = getChar(*infile_ptr);
	}
	getChar(*infile_ptr); // ����"="

	int n; *infile_ptr >> n;
	//cout << "����n���..." << "n = " << n << endl;

	string* v = new string[n + 2]; // ���Ķ���Ԫ�أ������������

	// ���뾰�����ƣ�����������"v="���棬�����в����ո񣬾�����Կո�ָ�
	(*infile_ptr).seekg(0); // ��λ���ļ���ʼ��
	ch = getChar(*infile_ptr);
	while (ch != 'v') { // ������"v"��ʼ����
		if (ch != '\n') skipOneLine();

		ch = getChar(*infile_ptr);
	}
	getChar(*infile_ptr); // ����"="

	for (int i = 0; i < n; i++) { // ���뾰������
		*infile_ptr >> v[i];
	}
	v[n] = "���"; v[n + 1] = "����";
	//cout << "����v���..." << "���磺v[0] = " << v[0] << endl;

	/*
	// ���������ʾ·����������"s="����
	(*infile_ptr).seekg(0); // ��λ���ļ���ʼ��
	ch = getChar(*infile_ptr);
	while (ch != 's') { // ������"s"��ʼ����
		if (ch != '\n') skipOneLine();

		ch = getChar(*infile_ptr);
	}
	getChar(*infile_ptr); // ����"="
	*infile_ptr >> path_max_num;
	//cout << "����s���..." << "s = " << path_max_num << endl;
	*/

	net_ptr = new Network<string, double>(v, n + 2);
	//cout << "����Network���..." << endl;

	delete[] v;

	// �������Ϣ
	(*infile_ptr).seekg(0); // ��λ���ļ���ʼ��
	ch = getChar(*infile_ptr);
	while (true) {
		while (ch != '(' && ch != EOF) { // ������'('��ʼ���У������ļ�����
			if (ch != '\n') skipOneLine();
			ch = getChar(*infile_ptr);
		}
		//cout << "�ҵ�\"(\"..." << endl;

		if (ch == EOF) break;

		string e1, e2;
		int v1, v2;
		double w;
		(*infile_ptr) >> e1 >> e2 >> w;
		//cout << "���붥����Ϣ���Ȩ�أ�" << e1 << "->" << e2 << ": " << w << "��" << endl;

		v1 = LocateVertex(e1); v2 = LocateVertex(e2);
		if (v1 == -1 || v2 == -1) { cout << "�߶���Ԫ�ش���" << endl; exit(-1); }
		net_ptr->insertEdge(v1, v2, w);
		//cout << "�����" << e1 << "->" << e2 << ": " << w << endl;

		ch = getChar(*infile_ptr);
	}
	//cout << "�������Ϣ���..." << endl;

	// ��ʼ��dist[][] path[][]
	//cout << "��ʼ��dist[][] path[][]" << endl;
	for (int u = 0; u < net_ptr->getVertexNum(); u++) {
		for (int v = 0; v < net_ptr->getVertexNum(); v++) {
			dist[u][v] = (u != v) ? net_ptr->getWeight(u, v) : 0;
			if (u != v && dist[u][v] < net_ptr->getInfinity()) path[u][v] = v; // ����<u, v>
			else path[u][v] = -1;
		}
	}
	// Floyd�㷨��ͼ���Ӷ������·��
	//cout << "Floyd�㷨��ͼ���Ӷ������·��" << endl;
	for (int k = 0; k < net_ptr->getVertexNum(); k++) {
		for (int i = 0; i < net_ptr->getVertexNum(); i++) {
			for (int j = 0; j < net_ptr->getVertexNum(); j++) {
				if (dist[i][j] > (dist[i][k] + dist[k][j])) {
					// i->k->j �� i->j ����
					dist[i][j] = dist[i][k] + dist[k][j];
					path[i][j] = path[i][k];
				}
			}
		}
	}
}

// ��������
ParkGuide::~ParkGuide() {
	net_ptr->~Network();
}

// ���й�԰��
int ParkGuide::run() {
	cout << "��ӭʹ�ù�԰��ϵͳ��" << endl;
	int choice = 0;
	while (true) {
		cout << endl << "��ѡ���ܣ�" << endl;
		cout << "1. ����������յ���ʾ���·��" << endl;
		cout << "2. ��ʾ�ܲ��ظ��������������о���Ĺ�԰·�ߣ�������������������ܾ������ж����һ�ε�·����" << endl;
		cout << "3. �˳�" << endl;
		cout << "(1 �� 2 �� 3)��"; cin >> choice;

		if (choice == 1) {
			string e1, e2;
			cout << "��㣺"; cin >> e1;
			cout << "�յ㣺"; cin >> e2;

			int v1 = LocateVertex(e1), v2 = LocateVertex(e2), k = path[v1][v2];
			Vertex<string, double>* table = net_ptr->getVertexTable();

			cout << "���·�ߣ�" << table[v1].data << "->";

			while (k != v2) {
				cout << table[k].data << "->";
				k = path[k][v2];
			}
			cout << table[v2].data << endl;

			cout << "·�߾��룺" << dist[v1][v2] << "��" << endl;
		}

		else if (choice == 2) {
			int ex = LocateVertex("����"), in = LocateVertex("���"), p[64], n = 1;
			p[0] = in;

			//cout << "��ʼѰ�Ҽ�·��" << endl;
			createPath(ex, in, p, n);
		}

		else if (choice == 3) {
			cout << endl << "ллʹ�ã�" << endl;
			return 0;
		}

		else {
			cout << endl << "������1��2��3���������������ַ���" << endl;
		}
	}
}
