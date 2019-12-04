#include "compression.h"

// 向目标文件写入一个比特
void Compression::writeBit(unsigned int bit) {
	buffer.bits++; // 缓存比特数加1
	buffer.ch = (buffer.ch << 1) | bit; // 将bit加到缓存字符中
	if (buffer.bits == 8) { // 缓存区已满
		fputc(buffer.ch, outfp); // 写入字符
		// 清空Buffer
		buffer.bits = 0;
		buffer.ch = 0;
	}

}
// 强行将字符缓冲写入目标文件：将不足8位的字符补充到8位，然后存入文件
void Compression::completeBit() {
	int len = buffer.bits;
	if (len > 0) { // 缓存有未达到8位的比特
		for (int i = 0; i < (8 - len); i++) {
			writeBit(0); // 写入0补位
		}
	}
}

// 构造函数
Compression::Compression() {
	tree_ptr = NULL;
	infp = NULL; 
	outfp = NULL;
	buffer.bits = 0;
	buffer.ch = 0;
}

// 析构函数
Compression::~Compression() {
	tree_ptr->~HuffmanTree();
	// cout << "析构Compression完成..." << endl;
}

// 压缩
void Compression::compress() {
	char inf[256], outf[256]; // 源文件

	cout << "请输入原文件名："; cin >> inf;
	infp = fopen(inf, "rb");
	if (infp == NULL) {
		cout << "打开源文件失败！（可能文件名输入错误）" << endl;
		exit(-1);
	}
	fgetc(infp); if (feof(infp)) { // fgetc让光标后移
		cout << "源文件为空！" << endl;
		exit(-1);
	}

	cout << "请输入目标文件名："; cin >> outf;
	outfp = fopen(outf, "wb");
	if (outfp == NULL) {
		cout << "打开压缩文件失败！（可能文件名输入错误）" << endl;
		exit(-1);
	}

	cout << "正在压缩，请稍等... ..." << endl;

	char ch[N] = { 0 }; // 字符数组
	unsigned long w[N] = { 0 }; // 权重数组

	// 之后会用到的变量
	unsigned long i, char_num = 0, size = 0; // i用于循环，char_num记录字符类型数，size记录字符个数
	char Char; // 从文件读一个字符

	rewind(infp); // 源文件指针指向文件开始处
	Char = fgetc(infp); // 从源文件取一个字符
	while (!feof(infp)) { // 统计字符出现频率，确定权重
		if ((unsigned int)Char > N-1) {
			cout << Char << ": " << (unsigned int)Char << endl;
			cout << "字符标号大于255！" << endl;
			exit(-1);
		}

		// 设置ch[], w[]
		if (w[(unsigned int)Char] == 0) { // Char没有出现过
			char_num++;
			ch[(unsigned int)Char] = Char;
		}

		size++;
		w[(unsigned int)Char]++;
		Char = fgetc(infp);
	}

	/*
	for (i = 0; i < N; i++) {
		if (w[i] != 0) {
			cout << ch[i] << ": " << w[i] << endl;
		}
	}
	*/
	

	// cout << "初始化完成..." << endl;

	tree_ptr = new HuffmanTree<char, unsigned long>(ch, w, N); // 生成哈夫曼树

	// cout << "创建哈夫曼树完成..." << endl;

	rewind(outfp);
	fwrite(&char_num, sizeof(unsigned long), 1, outfp); // 向目标文件写入源文件信息，有char_num类型的字符
	// cout << char_num << "存入" << endl;
	fwrite(&size, sizeof(unsigned long), 1, outfp); // 向目标文件写入源文件大小，有size个字符
	// cout << size << "存入" << endl;
	for (i = 0; i < N; i++) {
		if (w[i] != 0) {
			fwrite(&i, sizeof(unsigned long), 1, outfp); // 写入字符标号
			fwrite(&w[i], sizeof(unsigned long), 1, outfp); // 写入字符出现频率
			// cout << i << ", " << w[i] << "存入" << endl;
		}
	}

	// cout << "写入文件基础信息完成..." << endl;

	// cout << "二进制信息：";

	buffer.bits = 0; buffer.ch = 0;
	rewind(infp);
	Char = fgetc(infp);
	while (!feof(infp)) {
		string temp_str = tree_ptr->encode(Char);
		// cout << temp_str;
		for (i = 0; i < temp_str.length(); i++) {
			if (temp_str[i] == '0') writeBit(0);
			else if (temp_str[i] == '1') writeBit(1); // 忽略'\0'
		}
		Char = fgetc(infp);
	}
	// cout << endl;
	completeBit();

	fclose(infp); fclose(outfp);
	cout << "压缩完成！" << endl;
}

// 解压
void Compression::decompress() {
	char inf[256], outf[256];

	cout << "请输入压缩文件名："; cin >> inf;
	infp = fopen(inf, "rb");
	if (infp == NULL) {
		cout << "打开压缩文件失败！（可能文件名输入错误）" << endl;
		exit(-1);
	}

	fgetc(infp); if (feof(infp)) {
		cout << "压缩文件内容为空！" << endl;
		exit(-1);
	}

	cout << "请输入目标文件名："; cin >> outf;
	outfp = fopen(outf, "wb");
	if (outfp == NULL) {
		cout << "打开目标文件失败！（可能文件名输入错误）" << endl;
		exit(-1);
	}
	cout << "正在解压，请稍等... ..." << endl;

	char ch[N] = { 0 }; // 字符数组
	unsigned long w[N] = { 0 }; // 权重数组

	// 之后会用到的变量
	unsigned long i, index, char_num, size; // i用于循环，index、char_num、size为压缩文件信息，分别为字符标号、字符类型数、字符个数
	char Char;
	string bits_str = ""; // 储存压缩文件二进制内容的字符串

	rewind(infp);
	fread(&char_num, sizeof(unsigned long), 1, infp); // 读取字符类型数
	// cout << char_num << "读取" << endl;
	fread(&size, sizeof(unsigned long), 1, infp); // 读取字符个数
	// cout << size << "读取" << endl;
	for (i = 0; i < char_num; i++) {
		fread(&index, sizeof(unsigned long), 1, infp); // 读取标号
		ch[index] = (char)index; // 设置ch[]
		fread(&w[index], sizeof(unsigned long), 1, infp); // 读取权重数组
		// cout << index << ", " << w[index] << "读取" << endl;
	}
	// cout << "读取压缩文件基本信息完成..." << endl;

	if (tree_ptr != NULL) delete []tree_ptr;
	tree_ptr = new HuffmanTree<char, unsigned long>(ch, w, N);

	unsigned long len = 0; // 解压的字符数
	Char = fgetc(infp);
	while (!feof(infp)) {
		unsigned char uc = (unsigned char)Char; // 转换为unsigned char
		for (i = 0; i < 8; i++) {
			if (uc < 128) bits_str += "0";
			else bits_str += "1"; // c为8位二进制数，c >= 128时，最高位为1
			uc <<= 1; // uc = uc << 1 左移一位
		}
		Char = fgetc(infp);
	}

	// cout << "二进制文件内容：" << bits_str << endl;

	string text = tree_ptr->decode(bits_str); //由二进制字符串转换为文本

	// cout << "文本信息(可能含冗余)：" << text << endl;

	for (i = 0; i < text.length(); i++) { // 向目标文件写入文本
		len++;
		fputc(text[i], outfp);
		if (len == size) break;
	}

	fclose(infp); fclose(outfp);
	cout << "解压完成！" << endl;
}