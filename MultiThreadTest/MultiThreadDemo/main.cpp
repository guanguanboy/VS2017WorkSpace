#include <iostream>
#include <thread>
#include <list>
#include <mutex>
class A
{
public:
	//���յ�����Ϣ���뵽һ�����е��߳�
	void inMsgRecvQueue()
	{
		for (int i = 0; i < 10000; ++i)
		{
			std::cout << "inMsgRecvQueue ִ�У�����һ��Ԫ��" << i << std::endl;

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
			msgRecvQueue.pop_front(); //�Ƴ�һ��Ԫ��
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
				std::cout << "outMsgRecvQueue ִ�У��Ƴ���Ԫ��: " << command << std::endl;
			}
			else
			{
				std::cout << "outMsgRecvQueue ִ�У���Ŀǰ��Ϣ������Ϊ��" << i << std::endl;
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