#pragma once
#include<functional>
#include<algorithm>
#include<vector>
#include<cassert>
template <typename Item,typename Comp = std::less<typename Item>>
class PriorityQueue
{
public:
	//コンストラクタ
	PriorityQueue() :
		m_items(),
		m_comp()
	{
	}
	//コンストラクタ
	explicit PriorityQueue(Comp comp) :
		m_items(),
		m_comp(comp)
	{
	}

	//データの追加
	void Push(const Item& item)
	{
		m_items.push_back(item);
		std::push_heap(m_items.begin(), m_items.end(), m_comp);
	}

	//データの取り出し
	Item Pop()
	{
		assert(!IsEmpty());
		std::pop_heap(m_items.begin(), m_items.end(), m_comp);
		Item item =m_items.back();
		m_items.pop_back();
		return item;
	}
	//優先順位の更新
	void Update()
	{
		std::make_heap(m_items.begin(), m_items.end(), m_comp);
	}
	//空の時true
	bool IsEmpty() const
	{
		return m_items.empty();
	}

	//消去
	void Clear()
	{
		m_items.clear();
	}

private:
	//データ
	std::vector<Item> m_items;
	//比較関数
	Comp m_comp;
};