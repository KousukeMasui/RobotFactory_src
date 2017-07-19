#pragma once
#include<functional>
#include<algorithm>
#include<vector>
#include<cassert>
template <typename Item,typename Comp = std::less<typename Item>>
class PriorityQueue
{
public:
	//�R���X�g���N�^
	PriorityQueue() :
		m_items(),
		m_comp()
	{
	}
	//�R���X�g���N�^
	explicit PriorityQueue(Comp comp) :
		m_items(),
		m_comp(comp)
	{
	}

	//�f�[�^�̒ǉ�
	void Push(const Item& item)
	{
		m_items.push_back(item);
		std::push_heap(m_items.begin(), m_items.end(), m_comp);
	}

	//�f�[�^�̎��o��
	Item Pop()
	{
		assert(!IsEmpty());
		std::pop_heap(m_items.begin(), m_items.end(), m_comp);
		Item item =m_items.back();
		m_items.pop_back();
		return item;
	}
	//�D�揇�ʂ̍X�V
	void Update()
	{
		std::make_heap(m_items.begin(), m_items.end(), m_comp);
	}
	//��̎�true
	bool IsEmpty() const
	{
		return m_items.empty();
	}

	//����
	void Clear()
	{
		m_items.clear();
	}

private:
	//�f�[�^
	std::vector<Item> m_items;
	//��r�֐�
	Comp m_comp;
};