#pragma once
#include<forward_list>
//重複をしないために変数に保存しておく
class OverlapData
{
public:
	//コンストラクタ
	OverlapData();
	//デストラクタ
	~OverlapData();

	//追加
	void Add(void* data);
	//削除
	void Remove(void* data);
	//中に格納されているか判定
	bool IsContains(void* data);
private:
	//データ
	std::forward_list<void*> m_data;
};