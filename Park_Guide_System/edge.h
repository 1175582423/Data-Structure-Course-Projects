// �ڽӱ�������
#pragma once

template <class WeightType>
class Edge {
public:
	int adjacency_vertex; // �ڽӵ�
	WeightType weight; // Ȩ��

	Edge() { // ���캯��
		adjacency_vertex = -1; // ����һ�����ڽӱ�߽���
		weight = 0;
	}

	Edge(int v, WeightType w) { // ���ι��캯��
		// �����ڽӵ�Ϊv��ȨΪw���ڽӱ�
		adjacency_vertex = v;
		weight = w;
	}
};