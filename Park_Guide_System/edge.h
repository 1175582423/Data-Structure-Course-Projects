// 邻接表网边类
#pragma once

template <class WeightType>
class Edge {
public:
	int adjacency_vertex; // 邻接点
	WeightType weight; // 权重

	Edge() { // 构造函数
		adjacency_vertex = -1; // 构造一个空邻接表边结点边
		weight = 0;
	}

	Edge(int v, WeightType w) { // 含参构造函数
		// 构造邻接点为v，权为w的邻接边
		adjacency_vertex = v;
		weight = w;
	}
};