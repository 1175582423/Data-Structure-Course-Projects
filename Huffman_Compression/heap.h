// С���ѣ�ÿ������ֵ��С�ڻ���������Һ��ӽ���ֵ��
#pragma once

// ��������Ԫ��
template<class ElemType>
void swap(ElemType& e1, ElemType& e2) {
	ElemType t;
	t = e1;
	e1 = e2;
	e2 = t;
}

template <class ElemType>
class Heap {
protected:
	ElemType* elem; // ����Ԫ�ص�����
	int size; // �����Ԫ�ظ���
	int count; // ��Ԫ�ظ���
	
	// elem[low .. high]�м�¼�Ĺؼ��ֳ�elem[low]���ⶼ����Ѷ���
	// ����elem[low]ʹ��elem[low .. high]���ؼ��ֳ�Ϊһ��С����
	void SiftAdjust(int low, int high);

public:
	Heap(int sz); // ���캯��
	Heap(ElemType e[], int cnt, int sz); // ���ι��캯��
	virtual ~Heap(); // ��������
	int getCount(); // ����count
	void outQueue(ElemType& e); // ɾ���Ѷ�Ԫ�ص�e
	void inQueue(const ElemType& e); // ����Ԫ��e
};

template <class ElemType>
void Heap<ElemType>::SiftAdjust(int low, int high) {
	// fΪ��������㣬iΪf������
	int f = low;
	int i = 2 * low + 1;
	while (i <= high) {
		if (i < high && elem[i] > elem[i + 1]) { // ���Ӵ����Һ���
			i++; // iָ���Һ���
		}
		if (elem[f] <= elem[i]) { // ��ΪС����
			break;
		}
		swap<ElemType>(elem[f], elem[i]);
		f = i;
		i = 2 * i + 1;
	}
}

template <class ElemType>
Heap<ElemType>::Heap(int sz) {
	elem = new ElemType[sz];
	size = sz;
	count = 0;
}

template <class ElemType>
Heap<ElemType>::Heap(ElemType e[], int cnt, int sz) {
	elem = new ElemType[sz];
	size = sz;
	count = cnt; // ���������һ�����Ϊcount-1����Ϊ��0��ʼ���
	for (int pos = 0; pos < cnt; pos++) {
		elem[pos] = e[pos];
	}
	for (int i = (count - 2) / 2; i >= 0; i--) { // elem[]����С����
		SiftAdjust(i, count - 1); // ֻ��Ҫ��֤���ڵ�С���ӽ�㣬ͬ�������С����ν
	}
}

template <class ElemType>
Heap<ElemType>::~Heap() {
	delete []elem;
}

template <class ElemType>
int Heap<ElemType>::getCount() {
	return count;
}

template <class ElemType>
void Heap<ElemType>::outQueue(ElemType& e) {
	e = elem[0];
	swap(elem[0], elem[count - 1]);
	SiftAdjust(0, count - 2); // ֻ��[count-1]������[0]��[1...count-2]��Ȼ����С����
	count--;
}

template <class ElemType>
void Heap<ElemType>::inQueue(const ElemType& e) {
	int cur_pos = count;
	count += 1;
	int parent = (cur_pos - 1) / 2; // ��ǰ���ڵ�λ��
	elem[cur_pos] = e;
	while (cur_pos > 0 && elem[cur_pos] < elem[parent]) { // elem[cur_pos]С��˫�ף����佻��
		swap<ElemType>(elem[cur_pos], elem[parent]);
		cur_pos = parent;
		parent = (cur_pos - 1) / 2;
	}
}