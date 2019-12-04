// 压缩类
#pragma once

#include "huffman.h"
#include <iostream>
#include <fstream>

const unsigned int N = 256; // ch[], w[]数组大小

// 在Huffman树中，字符的哈夫曼编码以比特为单位，而当其压缩文件时，压缩文件最少以字节（字符为单位存储）(fgetc())
// 所以定义字符缓存器，自动将比特转换为字节
struct BufferType {
	char ch;
	unsigned int bits;
};

// 哈夫曼压缩类
class Compression {
protected:
	HuffmanTree<char, unsigned long>* tree_ptr; // 哈夫曼树指针
	FILE* infp, * outfp; // 文件指针
	BufferType buffer; // 字符缓冲器

	void writeBit(unsigned int bit); // 向目标文件写入一个比特
	void completeBit(); // 强行将字符缓冲写入目标文件：将不足8位的字符补充到8位，然后存入文件

public:
	Compression(); // 构造函数
	~Compression(); // 析构函数
	void compress(); // 压缩
	void decompress(); // 解压
};