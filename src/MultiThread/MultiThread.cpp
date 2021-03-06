#include "MultiThread.h"
#include<future>
MultiThread::MultiThread(const std::function<void()>& updateFunc):
	m_updateFunc(updateFunc)
{
}
MultiThread::~MultiThread()
{
}
void MultiThread::Create(const std::function<void()>& multiThreadFunc, const std::function<void()>& endFunc)
{
	std::thread th1(multiThreadFunc);
	//std::thread updateThread(m_updateFunc);
	//並列処理
	//m_updateFunc();
	//updateThread.detach();
	th1.join();
	//待機後の処理
	endFunc();
}