// ��԰����
#pragma once

#include "network.h"
#include <fstream>
#include <string>

class ParkGuide {
private:
	Network<string, double>* net_ptr; // �й�԰��Ϣ��������
	ifstream* infile_ptr; // ������Ϣ���ļ�
	double dist[64][64]; // ����u, v֮�����·������dict[u][v]
	int path[64][64]; // ��u��v֮�����·��path[u][v]��u�ĺ�һ�������

	int LocateVertex(const string& e); // ���ض��������е�λ��
	void skipOneLine(); // �����ļ�һ��
	void showPath(int* p, int path_vertex_num); // ������·��
	void createPath(int ex, int v, int* p, int path_vertex_num); // ���ɲ��������·��

public:
	ParkGuide(ifstream* inf_ptr); // ���캯��
	virtual ~ParkGuide(); // ��������
	int run(); // ���й�԰��
};

static char getChar(istream& inStream) { // ��������inStream�������ո��Ʊ����ȡһ�ַ�
	char ch;
	while ((ch = (inStream).peek()) != EOF // peek()�������������н���1�ַ�,���ĵ�ǰλ�ò���
		&& ((ch = (inStream).get()) == ' ' || ch == '\t')) { // get()�������������н���1�ַ�,���ĵ�ǰλ�������1��λ��
		
		return ch;
	}
}