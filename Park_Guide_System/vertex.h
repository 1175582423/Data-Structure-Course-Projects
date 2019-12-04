// �ڽӱ�����������
#pragma once

#include "linklist.h"
#include "edge.h"

template <class ElemType, class WeightType>
class Vertex {
public:
	ElemType data; // ����Ԫ��ֵ
	LinkList<Edge<WeightType>>* edge_list_ptr; // ָ���ڽӱ��ָ��

	Vertex() { // ���캯��
		edge_list_ptr = NULL; // ָ���ڽ������ָ��Ϊ��
	}

	Vertex(ElemType item, LinkList<Edge<WeightType>>* e_list_ptr) { // ���ι��캯��
		
		data = item; // ��������
		edge_list_ptr = e_list_ptr; // ָ���ڽ������ָ��
	}
};