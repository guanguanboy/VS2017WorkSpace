#include <stdio.h>
#include <iostream>

using namespace std;


struct test1 {
	char c;
	int i;
};

//#pragma pack(push,4) //���ֽڶ���
#pragma pack(push,1) //һ�ֽڶ���
//linux ���ֽڶ���Ļ�ʹ�� struct __attribute__((__packed__)) test2 {

struct test2 {
	char c;
	int i;
};

int main()
{
	cout << "size of test1:" << sizeof(struct test1) << endl;
	cout << "size of test2:" << sizeof(struct test2) << endl;

	system("pause");
	return 0;
}

