#include <iostream>
#include <thread>
#include <mutex>
#include <condition_variable>

std::mutex mtx; //全局互斥锁
std::condition_variable cv; //全局条件变量
bool ready = false;  //全局标志位

void do_print_id(int id)
{
	std::unique_lock<std::mutex> lck(mtx);
	while (!ready) //如果标志位不为true则等待...
	{
		cv.wait(lck); //当前线程被阻塞
	}

	//当全局标志位变为true之后，
	//线程被唤醒，继续往下执行，打印线程编号
	std::cout << "thread " << id << '\n';
}

void go()
{
	std::unique_lock<std::mutex> lck(mtx);
	ready = true; // 设置全局标志位为true
	cv.notify_all(); //唤醒所有线程
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