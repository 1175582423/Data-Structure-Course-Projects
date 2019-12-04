#include "compression.h"

// ��Ŀ���ļ�д��һ������
void Compression::writeBit(unsigned int bit) {
	buffer.bits++; // �����������1
	buffer.ch = (buffer.ch << 1) | bit; // ��bit�ӵ������ַ���
	if (buffer.bits == 8) { // ����������
		fputc(buffer.ch, outfp); // д���ַ�
		// ���Buffer
		buffer.bits = 0;
		buffer.ch = 0;
	}

}
// ǿ�н��ַ�����д��Ŀ���ļ���������8λ���ַ����䵽8λ��Ȼ������ļ�
void Compression::completeBit() {
	int len = buffer.bits;
	if (len > 0) { // ������δ�ﵽ8λ�ı���
		for (int i = 0; i < (8 - len); i++) {
			writeBit(0); // д��0��λ
		}
	}
}

// ���캯��
Compression::Compression() {
	tree_ptr = NULL;
	infp = NULL; 
	outfp = NULL;
	buffer.bits = 0;
	buffer.ch = 0;
}

// ��������
Compression::~Compression() {
	tree_ptr->~HuffmanTree();
	// cout << "����Compression���..." << endl;
}

// ѹ��
void Compression::compress() {
	char inf[256], outf[256]; // Դ�ļ�

	cout << "������ԭ�ļ�����"; cin >> inf;
	infp = fopen(inf, "rb");
	if (infp == NULL) {
		cout << "��Դ�ļ�ʧ�ܣ��������ļ����������" << endl;
		exit(-1);
	}
	fgetc(infp); if (feof(infp)) { // fgetc�ù�����
		cout << "Դ�ļ�Ϊ�գ�" << endl;
		exit(-1);
	}

	cout << "������Ŀ���ļ�����"; cin >> outf;
	outfp = fopen(outf, "wb");
	if (outfp == NULL) {
		cout << "��ѹ���ļ�ʧ�ܣ��������ļ����������" << endl;
		exit(-1);
	}

	cout << "����ѹ�������Ե�... ..." << endl;

	char ch[N] = { 0 }; // �ַ�����
	unsigned long w[N] = { 0 }; // Ȩ������

	// ֮����õ��ı���
	unsigned long i, char_num = 0, size = 0; // i����ѭ����char_num��¼�ַ���������size��¼�ַ�����
	char Char; // ���ļ���һ���ַ�

	rewind(infp); // Դ�ļ�ָ��ָ���ļ���ʼ��
	Char = fgetc(infp); // ��Դ�ļ�ȡһ���ַ�
	while (!feof(infp)) { // ͳ���ַ�����Ƶ�ʣ�ȷ��Ȩ��
		if ((unsigned int)Char > N-1) {
			cout << Char << ": " << (unsigned int)Char << endl;
			cout << "�ַ���Ŵ���255��" << endl;
			exit(-1);
		}

		// ����ch[], w[]
		if (w[(unsigned int)Char] == 0) { // Charû�г��ֹ�
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
	

	// cout << "��ʼ�����..." << endl;

	tree_ptr = new HuffmanTree<char, unsigned long>(ch, w, N); // ���ɹ�������

	// cout << "���������������..." << endl;

	rewind(outfp);
	fwrite(&char_num, sizeof(unsigned long), 1, outfp); // ��Ŀ���ļ�д��Դ�ļ���Ϣ����char_num���͵��ַ�
	// cout << char_num << "����" << endl;
	fwrite(&size, sizeof(unsigned long), 1, outfp); // ��Ŀ���ļ�д��Դ�ļ���С����size���ַ�
	// cout << size << "����" << endl;
	for (i = 0; i < N; i++) {
		if (w[i] != 0) {
			fwrite(&i, sizeof(unsigned long), 1, outfp); // д���ַ����
			fwrite(&w[i], sizeof(unsigned long), 1, outfp); // д���ַ�����Ƶ��
			// cout << i << ", " << w[i] << "����" << endl;
		}
	}

	// cout << "д���ļ�������Ϣ���..." << endl;

	// cout << "��������Ϣ��";

	buffer.bits = 0; buffer.ch = 0;
	rewind(infp);
	Char = fgetc(infp);
	while (!feof(infp)) {
		string temp_str = tree_ptr->encode(Char);
		// cout << temp_str;
		for (i = 0; i < temp_str.length(); i++) {
			if (temp_str[i] == '0') writeBit(0);
			else if (temp_str[i] == '1') writeBit(1); // ����'\0'
		}
		Char = fgetc(infp);
	}
	// cout << endl;
	completeBit();

	fclose(infp); fclose(outfp);
	cout << "ѹ����ɣ�" << endl;
}

// ��ѹ
void Compression::decompress() {
	char inf[256], outf[256];

	cout << "������ѹ���ļ�����"; cin >> inf;
	infp = fopen(inf, "rb");
	if (infp == NULL) {
		cout << "��ѹ���ļ�ʧ�ܣ��������ļ����������" << endl;
		exit(-1);
	}

	fgetc(infp); if (feof(infp)) {
		cout << "ѹ���ļ�����Ϊ�գ�" << endl;
		exit(-1);
	}

	cout << "������Ŀ���ļ�����"; cin >> outf;
	outfp = fopen(outf, "wb");
	if (outfp == NULL) {
		cout << "��Ŀ���ļ�ʧ�ܣ��������ļ����������" << endl;
		exit(-1);
	}
	cout << "���ڽ�ѹ�����Ե�... ..." << endl;

	char ch[N] = { 0 }; // �ַ�����
	unsigned long w[N] = { 0 }; // Ȩ������

	// ֮����õ��ı���
	unsigned long i, index, char_num, size; // i����ѭ����index��char_num��sizeΪѹ���ļ���Ϣ���ֱ�Ϊ�ַ���š��ַ����������ַ�����
	char Char;
	string bits_str = ""; // ����ѹ���ļ����������ݵ��ַ���

	rewind(infp);
	fread(&char_num, sizeof(unsigned long), 1, infp); // ��ȡ�ַ�������
	// cout << char_num << "��ȡ" << endl;
	fread(&size, sizeof(unsigned long), 1, infp); // ��ȡ�ַ�����
	// cout << size << "��ȡ" << endl;
	for (i = 0; i < char_num; i++) {
		fread(&index, sizeof(unsigned long), 1, infp); // ��ȡ���
		ch[index] = (char)index; // ����ch[]
		fread(&w[index], sizeof(unsigned long), 1, infp); // ��ȡȨ������
		// cout << index << ", " << w[index] << "��ȡ" << endl;
	}
	// cout << "��ȡѹ���ļ�������Ϣ���..." << endl;

	if (tree_ptr != NULL) delete []tree_ptr;
	tree_ptr = new HuffmanTree<char, unsigned long>(ch, w, N);

	unsigned long len = 0; // ��ѹ���ַ���
	Char = fgetc(infp);
	while (!feof(infp)) {
		unsigned char uc = (unsigned char)Char; // ת��Ϊunsigned char
		for (i = 0; i < 8; i++) {
			if (uc < 128) bits_str += "0";
			else bits_str += "1"; // cΪ8λ����������c >= 128ʱ�����λΪ1
			uc <<= 1; // uc = uc << 1 ����һλ
		}
		Char = fgetc(infp);
	}

	// cout << "�������ļ����ݣ�" << bits_str << endl;

	string text = tree_ptr->decode(bits_str); //�ɶ������ַ���ת��Ϊ�ı�

	// cout << "�ı���Ϣ(���ܺ�����)��" << text << endl;

	for (i = 0; i < text.length(); i++) { // ��Ŀ���ļ�д���ı�
		len++;
		fputc(text[i], outfp);
		if (len == size) break;
	}

	fclose(infp); fclose(outfp);
	cout << "��ѹ��ɣ�" << endl;
}