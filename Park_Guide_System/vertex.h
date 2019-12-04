// 邻接表网顶点结点类
#pragma once

#include "linklist.h"
#include "edge.h"

template <class ElemType, class WeightType>
class Vertex {
public:
	ElemType data; // 数据元素值
	LinkList<Edge<WeightType>>* edge_list_ptr; // 指向邻接表的指针

	Vertex() { // 构造函数
		edge_list_ptr = NULL; // 指向邻接链表的指针为空
	}

	Vertex(ElemType item, LinkList<Edge<WeightType>>* e_list_ptr) { // 含参构造函数
		
		data = item; // 顶点数据
		edge_list_ptr = e_list_ptr; // 指向邻接链表的指针
	}
};