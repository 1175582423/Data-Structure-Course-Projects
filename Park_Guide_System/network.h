// 邻接表无向网类
#pragma once

#include "vertex.h"

#define DEFAULT_INFINITY 1000000

template <class ElemType, class WeightType>
class Network {
protected:
	int vertex_num, edge_num; // 顶点、边数
	Vertex<ElemType, WeightType>* vertex_table; // 顶点表
	mutable bool* tag; // 标志结点有没有被访问过
	WeightType infinity = DEFAULT_INFINITY; // 无穷大

	int Index(const LinkList<Edge<WeightType>>* la, int v) const; // 定位顶点v在邻接链表中的位置

public:
	Network(ElemType v[], int v_num, WeightType inf = (WeightType)DEFAULT_INFINITY); // 构造函数
	~Network(); // 析构函数
	WeightType getInfinity() const; // 返回无穷大
	int getVertexNum() const; // 返回顶点数
	int getEdgeNum() const; // 返回边数
	Vertex<ElemType, WeightType>* getVertexTable() const; // 返回顶点表
	WeightType getWeight(int v1, int v2); // 返回顶点为v1和v2的边的权值
	bool getTag(int v) const; // 返回v标志，即是否被访问过
	void setTag(int v, bool val) const; // 设置v的标志为val
	int FirstAdjVex(int v) const; // 返回顶点v的第一个邻接点
	int NextAdjVex(int v1, int v2) const; // 返回顶点v1的相对于v2的下一个邻接点
	void insertEdge(int v1, int v2, WeightType w); // 插入顶点为v1和v2,权为w的边
};


// Network类成员函数实现

template <class ElemType, class WeightType>
int Network<ElemType, WeightType>::Index(const LinkList<Edge<WeightType>>* la, int v) const {
	Edge<WeightType> tmp_edge;
	int cur_pos = la->getCurPosition();

	la->getElem(cur_pos, tmp_edge);
	if (tmp_edge.adjacency_vertex == v) return cur_pos;
	
	cur_pos = 1;
	for (cur_pos = 1; cur_pos <= la->length(); cur_pos++) { // 链表含头结点，所以从1开始
		la->getElem(cur_pos, tmp_edge);
		if (tmp_edge.adjacency_vertex == v) break;
	}

	return cur_pos;
}

template<class ElemType, class WeightType>
Network<ElemType, WeightType>::Network(ElemType v[], int v_num, WeightType inf) {
	//cout << "开始建立Network对象..." << endl;

	if (v_num < 0) { cout << "顶点个数不能为负" << endl; exit(-1); }

	infinity = inf;
	vertex_num = v_num;
	edge_num = 0;

	tag = new bool[vertex_num];
	for (int i = 0; i < vertex_num; i++) {
		tag[i] = false; // false为未被访问，true为访问过
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
	if (v1 < 0 || v1 >= vertex_num) { cout << "v1不合法!" << endl; exit(-1); }
	if (v2 < 0 || v2 >= vertex_num) { cout << "v2不合法!" << endl; exit(-1); }

	Edge<WeightType> tmp_edge;
	int cur_pos = Index(vertex_table[v1].edge_list_ptr, v2);
	if (cur_pos <= vertex_table[v1].edge_list_ptr->length()) { // 存在<v1, v2>
		vertex_table[v1].edge_list_ptr->getElem(cur_pos, tmp_edge);
		return tmp_edge.weight;
	}
	else { // 不存在<v1, v2>
		return infinity;
	}
}

template<class ElemType, class WeightType>
bool Network<ElemType, WeightType>::getTag(int v) const {
	if (v < 0 || v >= vertex_num) cout << "v大小非法！" << endl;
	
	return tag[v];
}

template<class ElemType, class WeightType>
void Network<ElemType, WeightType>::setTag(int v, bool val) const {
	if (v < 0 || v >= vertex_num) cout << "v大小非法！" << endl;

	tag[v] = val;
}

template <class ElemType, class WeightType>
int Network<ElemType, WeightType>::FirstAdjVex(int v) const {
	if (v < 0 || v >= vertex_num) {
		cout << "v大小非法！" << endl; exit(-1);
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
	if (v1 < 0 || v1 >= vertex_num) { cout << "v1大小非法！" << endl; exit(-1); }
	if (v2 < 0 || v2 >= vertex_num) { cout << "v1大小非法！" << endl; exit(-1); }
	if (v1 == v2) cout << "v1不能等于v2！" << endl;

	if (vertex_table[v1].edge_list_ptr == NULL) { 
		return -1;
	}

	Edge<WeightType> tmp_edge;
	int cur_pos = Index(vertex_table[v1].edge_list_ptr, v2); // 取出v2在邻接链表中的位置
	// 存在下一个邻接点
	if (cur_pos < vertex_table[v1].edge_list_ptr->length()) {
		vertex_table[v1].edge_list_ptr->getElem(cur_pos + 1, tmp_edge); // 取出后继
		return tmp_edge.adjacency_vertex;
	}
	// 不存在下一个邻接点
	else {
		return -1;
	}
}

template<class ElemType, class WeightType>
void Network<ElemType, WeightType>::insertEdge(int v1, int v2, WeightType w) {
	if (v1 < 0 || v1 >= vertex_num) { cout << "v1大小不合法！" << endl; exit(-1); }
	if (v2 < 0 || v2 >= vertex_num) { cout << "v2大小不合法！" << endl; exit(-1); }
	if (v1 == v2) { cout << "v1不能等于v2！" << endl; exit(-1); }
	if (w == infinity) { cout << "w不能为无穷大！" << endl; exit(-1); }

	Edge<WeightType> tmp_edge;

	// 插入<v1, v2>
	if (vertex_table[v1].edge_list_ptr == NULL) { // 空链表
		//cout << "创建顶点表：" << v1 << endl;
		vertex_table[v1].edge_list_ptr = new LinkList<Edge<WeightType>>;
	}
	
	int cur_pos = Index(vertex_table[v1].edge_list_ptr, v2);
	if (cur_pos <= vertex_table[v1].edge_list_ptr->length()) { // 存在边<v1, v2>
		vertex_table[v1].edge_list_ptr->getElem(cur_pos, tmp_edge);
		tmp_edge.weight = w;
		vertex_table[v1].edge_list_ptr->setElem(cur_pos, tmp_edge);
	}
	else { // 不存在边<v1, v2>
		tmp_edge.adjacency_vertex = v2;
		tmp_edge.weight = w;

		vertex_table[v1].edge_list_ptr->insert(cur_pos, tmp_edge);
		edge_num++;
	}

	// 插入<v2, v1>
	if (vertex_table[v2].edge_list_ptr == NULL) { // 空链表
		vertex_table[v2].edge_list_ptr = new LinkList<Edge<WeightType>>;
	}

	cur_pos = Index(vertex_table[v2].edge_list_ptr, v1);
	if (cur_pos <= vertex_table[v2].edge_list_ptr->length()) { // 存在边<v2, v1>
		vertex_table[v2].edge_list_ptr->getElem(cur_pos, tmp_edge);
		tmp_edge.weight = w;
		vertex_table[v2].edge_list_ptr->setElem(cur_pos, tmp_edge);
	}
	else { // 不存在边<v2, v1>
		tmp_edge.adjacency_vertex = v1;
		tmp_edge.weight = w;

		vertex_table[v2].edge_list_ptr->insert(cur_pos, tmp_edge);
		edge_num++;
	}
}
