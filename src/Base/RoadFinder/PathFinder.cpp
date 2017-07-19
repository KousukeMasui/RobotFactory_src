#include "PathFinder.h"

#include"Map/FieldMap.h"
#include"List/AstarOpenList.h"
#include"List/DijkstraOpenList.h"
#include"List/RangeOpenList.h"
//コンストラクタ

PathFinder::PathFinder(FieldMap & map) :
	m_grid(map),
	targetNum(0)
{

}

//目標位置を検索

std::vector<NodePtr> PathFinder::FindTarget(const Point2 & start, const Point2 & target)
{
	AstarOpenList list(m_grid[target]);
	return FindPath(m_grid, list, m_grid[start]);
}

//複数の目標位置を検索

std::vector<NodePtr> PathFinder::FindMultiTarget(const Point2 & start)
{
	DijkstraOpenList list;
	return FindPath(m_grid, list, m_grid[start]);
}

//移動範囲の検索

void PathFinder::findSearchRange(const Point2 & start, float cost)
{
	RangeOpenList list(cost);
	list.Start(m_grid[start]);
	while (!list.IsEmpty())
	{
		list.Pop();
		m_grid.neighbors(list.GetFront(), [&](const NodePtr& node) {list.Push(node); });
		//m_grid.draw();//デバッグ表示
	}
}

//目標地点の追加

void PathFinder::AddTarget(const Point2 & target)
{
	m_grid[target]->TargetSet();
	targetNum++;
}
void PathFinder::AddTargets(const std::vector<Point2>& targets)
{
	for (auto target : targets)
	{
		AddTarget(target);
	}
}
//ノードの取得
NodePtr PathFinder::operator [](const Point2& position) const
{
	return m_grid[position];
}

//検索パスノードの作成

std::vector<NodePtr> PathFinder::CreatePath(const Point2 & target) const
{
	return m_grid.createPath(m_grid[target]);
}
