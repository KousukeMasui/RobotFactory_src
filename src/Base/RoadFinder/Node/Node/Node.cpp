#include "Node.h"
#include"Math/Point2/Point2.h"
// コンストラクタ

 Node::Node(const Point2 & position, int index) :
	m_position(position),
	m_isWalk(index ==0),
	m_cost(1.0f),
	m_parent(nullptr),
	m_isOpened(false),
	m_isClose(false),
	m_isTarget(false),
	m_totalCost(0.0f),
	m_estimate(0.0f),
	m_isPath(false),
	 m_index(index)
{
}

 int Node::Index()
 {
	 return m_index;
 }

// 座標の取得

 Point2 Node::position() const
{
	return m_position;
}

//合計コストの取得

 float Node::Total() const
{
	return m_totalCost;
}

// 更新する

 void Node::update(Node & parent, float h)
{
	m_totalCost = parent.m_totalCost + m_cost;
	m_estimate = m_totalCost + h;
	m_parent = &parent;
}

//検索中にする

 void Node::Open()
{
	m_isOpened = true;
}

//検索中ノードか

 bool Node::IsOpened()
{
	return m_isOpened;
}

 bool Node::IsTarget() const
{
	return m_isTarget;
}

 void Node::TargetSet()
{
	m_isTarget = true;
}

// 検索終了ノードか？

 bool Node::closed() const
{
	return m_isClose;
}

// 移動可能か？

 bool Node::walkable() const
{
	return m_isWalk;
}

// 検索終了にする

 void Node::close()
{
	m_isClose = true;
}

 void Node::SetWalkable(bool isWalkable)
 {
	 m_isWalk = isWalkable;
 }
 bool Node::IsUpdate(const Node & parent) const
{
	if (!m_isOpened) return true;
	if ((parent.m_totalCost + m_cost) < m_totalCost) return true;
	return false;
}

// 目的地からスタート地点までさかのぼる

 void Node::backtrack(std::function<void(Node&node)> f)
{
	for (auto node = this; node != nullptr; node = node->m_parent)
	{
		f(*node);
		node->m_isPath = true;	// デバッグ用
	}
}

 float Node::Distance(const Node & target) const
{
	return m_position.Distance(target.m_position);
}

//比較関数
bool Node::operator < (const Node& other) const
{
	return m_estimate < other.m_estimate;
}

// 文字列化（デバッグ用）

 std::string Node::to_string() const
{
	if (!m_isWalk)	return "■";
	if (m_isPath)	return "▽";
	if (m_isClose)	return "×";
	if (m_isOpened)	return "○";
	if (m_isTarget) return "◎";
	return	"　";
}
