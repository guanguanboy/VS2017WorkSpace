#include <thread>
#include <iostream>
#include <mutex>

//void Fun_1(unsigned int &counter);
//void Fun_2(unsigned int &counter);

unsigned int counter = 0;
std::mutex mtx;

void Fun_1()
{
	while (true)
	{
		++counter;
		if (counter < 1000)
		{
			std::cout << "Function 1 counting " << counter << "...\n";
		}
		else
		{
			break;
		}
	}
}

void Fun_2()
{
	while (true)
	{
		++counter;
		if (counter < 1000)
		{
			std::cout << "Function 2 counting" << counter << "...\n";
		}
		else
		{
			break;
		}
	}
}

#if 0
int main()
{
	std::thread thrd_1(Fun_1);
	std::thread thrd_2(Fun_2);

	thrd_1.join();
	thrd_2.join();

	system("pause");

	return 0;
}

#endif

void Fun_1_protected()
{
	while (true)
	{
		std::lock_guard<std::mutex> mtx_locker(mtx);
		++counter;
		if (counter < 1000)
		{
			std::cout << "Function 1 counting " << counter << "...\n";
		}
		else
		{
			break;
		}
	}
}

void Fun_2_protected()
{
	while (true)
	{
		std::lock_guard<std::mutex> mtx_locker(mtx);
		++counter;
		if (counter < 1000)
		{
			std::cout << "Function 2 counting " << counter << "...\n";
		}
		else
		{
			break;
		}
	}
}

int main()
{
	std::thread thrd_1(Fun_1_protected);
	std::thread thrd_2(Fun_2_protected);

	thrd_1.join();
	thrd_2.join();

	system("pause");

	return 0;
}