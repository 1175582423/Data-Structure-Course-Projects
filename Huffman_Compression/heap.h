// 小顶堆（每个结点的值都小于或等于其左右孩子结点的值）
#pragma once

// 交换两个元素
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
	ElemType* elem; // 储存元素的数组
	int size; // 堆最大元素个数
	int count; // 堆元素个数
	
	// elem[low .. high]中记录的关键字除elem[low]以外都满足堆定义
	// 调整elem[low]使其elem[low .. high]按关键字成为一个小顶堆
	void SiftAdjust(int low, int high);

public:
	Heap(int sz); // 构造函数
	Heap(ElemType e[], int cnt, int sz); // 含参构造函数
	virtual ~Heap(); // 析构函数
	int getCount(); // 返回count
	void outQueue(ElemType& e); // 删除堆顶元素到e
	void inQueue(const ElemType& e); // 插入元素e
};

template <class ElemType>
void Heap<ElemType>::SiftAdjust(int low, int high) {
	// f为被调整结点，i为f的左孩子
	int f = low;
	int i = 2 * low + 1;
	while (i <= high) {
		if (i < high && elem[i] > elem[i + 1]) { // 左孩子大于右孩子
			i++; // i指向右孩子
		}
		if (elem[f] <= elem[i]) { // 已为小顶堆
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
	count = cnt; // 二叉树最后一个标号为count-1，因为从0开始标号
	for (int pos = 0; pos < cnt; pos++) {
		elem[pos] = e[pos];
	}
	for (int i = (count - 2) / 2; i >= 0; i--) { // elem[]建立小顶堆
		SiftAdjust(i, count - 1); // 只需要保证父节点小于子结点，同级结点间大小无所谓
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
	SiftAdjust(0, count - 2); // 只把[count-1]换到了[0]，[1...count-2]仍然满足小顶堆
	count--;
}

template <class ElemType>
void Heap<ElemType>::inQueue(const ElemType& e) {
	int cur_pos = count;
	count += 1;
	int parent = (cur_pos - 1) / 2; // 当前父节点位置
	elem[cur_pos] = e;
	while (cur_pos > 0 && elem[cur_pos] < elem[parent]) { // elem[cur_pos]小于双亲，与其交换
		swap<ElemType>(elem[cur_pos], elem[parent]);
		cur_pos = parent;
		parent = (cur_pos - 1) / 2;
	}
}