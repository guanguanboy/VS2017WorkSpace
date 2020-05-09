#include <iostream>
#include <string>
#include <fstream> 
#include <iostream>
using namespace std;

int main()
{
	ifstream txtfile;//打开读取的文件
	ofstream txt01;//保存的文件
	ofstream txt02;//保存的文件
	string temp;
	int index = 0;//用于判断奇偶

	txtfile.open("0.txt", ios::in);

	while (!txtfile.eof())            // 若未到文件结束一直循环
	{

		getline(txtfile, temp);//一行一行读取
		if (index % 2 == 0)//判断除以2的余数，即为奇偶的判断
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
	txtfile.close();   //关闭文件
	txtfile.close();
	txt01.close();
	txt02.close();

	return 0;
}

