#include <iostream>
#include <string>
#include <fstream> 
#include <iostream>
using namespace std;

int main()
{
	ifstream txtfile;//�򿪶�ȡ���ļ�
	ofstream txt01;//������ļ�
	ofstream txt02;//������ļ�
	string temp;
	int index = 0;//�����ж���ż

	txtfile.open("0.txt", ios::in);

	while (!txtfile.eof())            // ��δ���ļ�����һֱѭ��
	{

		getline(txtfile, temp);//һ��һ�ж�ȡ
		if (index % 2 == 0)//�жϳ���2����������Ϊ��ż���ж�
		{
			txt01.open("1.txt", ios::app);
			txt01 << temp;
			txt01 << endl;
			txt01.close();
		}
		else
		{
			txt02.open("2.txt", ios::app);
			txt02 << temp;
			txt02 << endl;
			txt02.close();
		}
		index++;
	}
	txtfile.close();   //�ر��ļ�
	txtfile.close();
	txt01.close();
	txt02.close();

	return 0;
}

