// �ڽӱ���������
#pragma once

#include "vertex.h"

#define DEFAULT_INFINITY 1000000

template <class ElemType, class WeightType>
class Network {
protected:
	int vertex_num, edge_num; // ���㡢����
	Vertex<ElemType, WeightType>* vertex_table; // �����
	mutable bool* tag; // ��־�����û�б����ʹ�
	WeightType infinity = DEFAULT_INFINITY; // �����

	int Index(const LinkList<Edge<WeightType>>* la, int v) const; // ��λ����v���ڽ������е�λ��

public:
	Network(ElemType v[], int v_num, WeightType inf = (WeightType)DEFAULT_INFINITY); // ���캯��
	~Network(); // ��������
	WeightType getInfinity() const; // ���������
	int getVertexNum() const; // ���ض�����
	int getEdgeNum() const; // ���ر���
	Vertex<ElemType, WeightType>* getVertexTable() const; // ���ض����
	WeightType getWeight(int v1, int v2); // ���ض���Ϊv1��v2�ıߵ�Ȩֵ
	bool getTag(int v) const; // ����v��־�����Ƿ񱻷��ʹ�
	void setTag(int v, bool val) const; // ����v�ı�־Ϊval
	int FirstAdjVex(int v) const; // ���ض���v�ĵ�һ���ڽӵ�
	int NextAdjVex(int v1, int v2) const; // ���ض���v1�������v2����һ���ڽӵ�
	void insertEdge(int v1, int v2, WeightType w); // ���붥��Ϊv1��v2,ȨΪw�ı�
};


// Network���Ա����ʵ��

template <class ElemType, class WeightType>
int Network<ElemType, WeightType>::Index(const LinkList<Edge<WeightType>>* la, int v) const {
	Edge<WeightType> tmp_edge;
	int cur_pos = la->getCurPosition();

	la->getElem(cur_pos, tmp_edge);
	if (tmp_edge.adjacency_vertex == v) return cur_pos;
	
	cur_pos = 1;
	for (cur_pos = 1; cur_pos <= la->length(); cur_pos++) { // ����ͷ��㣬���Դ�1��ʼ
		la->getElem(cur_pos, tmp_edge);
		if (tmp_edge.adjacency_vertex == v) break;
	}

	return cur_pos;
}

template<class ElemType, class WeightType>
Network<ElemType, WeightType>::Network(ElemType v[], int v_num, WeightType inf) {
	//cout << "��ʼ����Network����..." << endl;

	if (v_num < 0) { cout << "�����������Ϊ��" << endl; exit(-1); }

	infinity = inf;
	vertex_num = v_num;
	edge_num = 0;

	tag = new bool[vertex_num];
	for (int i = 0; i < vertex_num; i++) {
		tag[i] = false; // falseΪδ�����ʣ�trueΪ���ʹ�
	}

	vertex_table = new Vertex<ElemType, WeightType>[vertex_num];
	for (int i = 0; i < vertex_num; i++) {
		vertex_table[i].data = v[i];
	}
}

template<class ElemType, class WeightType>
Network<ElemType, WeightType>::~Network() {
	delete []tag;
	for (int i = 0; i < vertex_num; i++) {
		if (vertex_table[i].edge_list_ptr != NULL) {
			delete vertex_table[i].edge_list_ptr;
		}
	}
	delete []vertex_table;
}

template<class ElemType, class WeightType>
WeightType Network<ElemType, WeightType>::getInfinity() const {
	return infinity;
}

template<class ElemType, class WeightType>
int Network<ElemType, WeightType>::getVertexNum() const {
	return vertex_num;
}

template<class ElemType, class WeightType>
int Network<ElemType, WeightType>::getEdgeNum() const {
	return edge_num;
}


template<class ElemType, class WeightType>
Vertex<ElemType, WeightType>* Network<ElemType, WeightType>::getVertexTable() const {
	return vertex_table;
}


template<class ElemType, class WeightType>
WeightType Network<ElemType, WeightType>::getWeight(int v1, int v2) {
	if (v1 < 0 || v1 >= vertex_num) { cout << "v1���Ϸ�!" << endl; exit(-1); }
	if (v2 < 0 || v2 >= vertex_num) { cout << "v2���Ϸ�!" << endl; exit(-1); }

	Edge<WeightType> tmp_edge;
	int cur_pos = Index(vertex_table[v1].edge_list_ptr, v2);
	if (cur_pos <= vertex_table[v1].edge_list_ptr->length()) { // ����<v1, v2>
		vertex_table[v1].edge_list_ptr->getElem(cur_pos, tmp_edge);
		return tmp_edge.weight;
	}
	else { // ������<v1, v2>
		return infinity;
	}
}

template<class ElemType, class WeightType>
bool Network<ElemType, WeightType>::getTag(int v) const {
	if (v < 0 || v >= vertex_num) cout << "v��С�Ƿ���" << endl;
	
	return tag[v];
}

template<class ElemType, class WeightType>
void Network<ElemType, WeightType>::setTag(int v, bool val) const {
	if (v < 0 || v >= vertex_num) cout << "v��С�Ƿ���" << endl;

	tag[v] = val;
}

template <class ElemType, class WeightType>
int Network<ElemType, WeightType>::FirstAdjVex(int v) const {
	if (v < 0 || v >= vertex_num) {
		cout << "v��С�Ƿ���" << endl; exit(-1);
	}
	else {
		if (vertex_table[v].edge_list_ptr == NULL) {
			
			return -1;
		}
		else {
			Edge<WeightType> tmp_edge;
			vertex_table[v].edge_list_ptr->getElem(1, tmp_edge);
			
			return tmp_edge.adjacency_vertex;
		}
	}
}

template <class ElemType, class WeightType>
int Network<ElemType, WeightType>::NextAdjVex(int v1, int v2) const {
	if (v1 < 0 || v1 >= vertex_num) { cout << "v1��С�Ƿ���" << endl; exit(-1); }
	if (v2 < 0 || v2 >= vertex_num) { cout << "v1��С�Ƿ���" << endl; exit(-1); }
	if (v1 == v2) cout << "v1���ܵ���v2��" << endl;

	if (vertex_table[v1].edge_list_ptr == NULL) { 
		return -1;
	}

	Edge<WeightType> tmp_edge;
	int cur_pos = Index(vertex_table[v1].edge_list_ptr, v2); // ȡ��v2���ڽ������е�λ��
	// ������һ���ڽӵ�
	if (cur_pos < vertex_table[v1].edge_list_ptr->length()) {
		vertex_table[v1].edge_list_ptr->getElem(cur_pos + 1, tmp_edge); // ȡ�����
		return tmp_edge.adjacency_vertex;
	}
	// ��������һ���ڽӵ�
	else {
		return -1;
	}
}

template<class ElemType, class WeightType>
void Network<ElemType, WeightType>::insertEdge(int v1, int v2, WeightType w) {
	if (v1 < 0 || v1 >= vertex_num) { cout << "v1��С���Ϸ���" << endl; exit(-1); }
	if (v2 < 0 || v2 >= vertex_num) { cout << "v2��С���Ϸ���" << endl; exit(-1); }
	if (v1 == v2) { cout << "v1���ܵ���v2��" << endl; exit(-1); }
	if (w == infinity) { cout << "w����Ϊ�����" << endl; exit(-1); }

	Edge<WeightType> tmp_edge;

	// ����<v1, v2>
	if (vertex_table[v1].edge_list_ptr == NULL) { // ������
		//cout << "���������" << v1 << endl;
		vertex_table[v1].edge_list_ptr = new LinkList<Edge<WeightType>>;
	}
	
	int cur_pos = Index(vertex_table[v1].edge_list_ptr, v2);
	if (cur_pos <= vertex_table[v1].edge_list_ptr->length()) { // ���ڱ�<v1, v2>
		vertex_table[v1].edge_list_ptr->getElem(cur_pos, tmp_edge);
		tmp_edge.weight = w;
		vertex_table[v1].edge_list_ptr->setElem(cur_pos, tmp_edge);
	}
	else { // �����ڱ�<v1, v2>
		tmp_edge.adjacency_vertex = v2;
		tmp_edge.weight = w;

		vertex_table[v1].edge_list_ptr->insert(cur_pos, tmp_edge);
		edge_num++;
	}

	// ����<v2, v1>
	if (vertex_table[v2].edge_list_ptr == NULL) { // ������
		vertex_table[v2].edge_list_ptr = new LinkList<Edge<WeightType>>;
	}

	cur_pos = Index(vertex_table[v2].edge_list_ptr, v1);
	if (cur_pos <= vertex_table[v2].edge_list_ptr->length()) { // ���ڱ�<v2, v1>
		vertex_table[v2].edge_list_ptr->getElem(cur_pos, tmp_edge);
		tmp_edge.weight = w;
		vertex_table[v2].edge_list_ptr->setElem(cur_pos, tmp_edge);
	}
	else { // �����ڱ�<v2, v1>
		tmp_edge.adjacency_vertex = v1;
		tmp_edge.weight = w;

		vertex_table[v2].edge_list_ptr->insert(cur_pos, tmp_edge);
		edge_num++;
	}
}
