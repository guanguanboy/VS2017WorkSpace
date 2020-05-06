#include <iostream>
#include <thread>
#include <list>
#include <mutex>
class A
{
public:
	//把收到的消息放入到一个队列的线程
	void inMsgRecvQueue()
	{
		for (int i = 0; i < 10000; ++i)
		{
			std::cout << "inMsgRecvQueue 执行，插入一个元素" << i << std::endl;

			//my_mutex.lock();
			std::lock_guard<std::mutex> my_guard(my_mutex);
			msgRecvQueue.push_back(i);
			//my_mutex.unlock();
			
		}
	}

	bool outMsgLULProc(int &command)
	{
		//my_mutex.lock();
		std::lock_guard<std::mutex> my_guard(my_mutex);
		if (!msgRecvQueue.empty())
		{
			command = msgRecvQueue.front();
			msgRecvQueue.pop_front(); //移除一个元素
			//my_mutex.unlock();
			return true;
		}

		//my_mutex.unlock();
		return false;
	}
	void outMsgRecvQueue()
	{
		int command = 0;

		for (int i = 0; i < 10000; ++i)
		{
			bool res = outMsgLULProc(command);
			if (true == res)
			{
				std::cout << "outMsgRecvQueue 执行，移除了元素: " << command << std::endl;
			}
			else
			{
				std::cout << "outMsgRecvQueue 执行，但目前消息队列中为空" << i << std::endl;
			}
		}

		std::cout << "end" << std::endl;
	}
private:
	std::list<int> msgRecvQueue;
	std::mutex my_mutex;
};

int main()
{
	A myobja;

	std::thread myOutMsgObj(&A::outMsgRecvQueue, &myobja);
	std::thread myInMsgObj(&A::inMsgRecvQueue, &myobja);
	myInMsgObj.join();
	myOutMsgObj.join();

}