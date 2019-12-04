// ѹ����
#pragma once

#include "huffman.h"
#include <iostream>
#include <fstream>

const unsigned int N = 256; // ch[], w[]�����С

// ��Huffman���У��ַ��Ĺ����������Ա���Ϊ��λ��������ѹ���ļ�ʱ��ѹ���ļ��������ֽڣ��ַ�Ϊ��λ�洢��(fgetc())
// ���Զ����ַ����������Զ�������ת��Ϊ�ֽ�
struct BufferType {
	char ch;
	unsigned int bits;
};

// ������ѹ����
class Compression {
protected:
	HuffmanTree<char, unsigned long>* tree_ptr; // ��������ָ��
	FILE* infp, * outfp; // �ļ�ָ��
	BufferType buffer; // �ַ�������

	void writeBit(unsigned int bit); // ��Ŀ���ļ�д��һ������
	void completeBit(); // ǿ�н��ַ�����д��Ŀ���ļ���������8λ���ַ����䵽8λ��Ȼ������ļ�

public:
	Compression(); // ���캯��
	~Compression(); // ��������
	void compress(); // ѹ��
	void decompress(); // ��ѹ
};