#pragma once
#include<future>
#include<forward_list>
//マルチスレッドを行うようのクラス
class MultiThread {
public:
	explicit MultiThread(const std::function<void()>& updateFunc);
	~MultiThread();
	//スレッド生成
	void Create(const std::function<void()>& multiThreadFunc
		,const std::function<void()>& endFunc);
private:
	const std::function<void()> m_updateFunc;
	std::forward_list<std::thread> m_threads;
};