#include <iostream>
#include <thread>
#include <mutex>
#include <condition_variable>

std::mutex mtx; //ȫ�ֻ�����
std::condition_variable cv; //ȫ����������
bool ready = false;  //ȫ�ֱ�־λ

void do_print_id(int id)
{
	std::unique_lock<std::mutex> lck(mtx);
	while (!ready) //�����־λ��Ϊtrue��ȴ�...
	{
		cv.wait(lck); //��ǰ�̱߳�����
	}

	//��ȫ�ֱ�־λ��Ϊtrue֮��
	//�̱߳����ѣ���������ִ�У���ӡ�̱߳��
	std::cout << "thread " << id << '\n';
}

void go()
{
	std::unique_lock<std::mutex> lck(mtx);
	ready = true; // ����ȫ�ֱ�־λΪtrue
	cv.notify_all(); //���������߳�
}

int main()
{
	std::thread thread_array[20];

	// spawn 10 threads
	for (int i = 0; i < 20; ++i)
	{
		thread_array[i] = std::thread(do_print_id, i);
	}

	std::cout << "20 threads ready to race...\n";
	go();

	for (auto & th : thread_array)
	{
		th.join();
	}

	return 0;
}