#pragma once
#include"Map/NodeGrid.h"

class FieldMap;
class AstarOpenList;
class DijkstraOpenList;
class RangeOpenList;
//経路探索クラス
class PathFinder
{
public:
	//コンストラクタ
	explicit PathFinder(FieldMap& map);

	//目標位置を検索
	std::vector<NodePtr> FindTarget(const Point2& start, const Point2& target);

	//複数の目標位置を検索
	std::vector<NodePtr> FindMultiTarget(const Point2& start);

	//複数の目標位置を検索
	std::vector<std::vector<NodePtr>> FindMultiTargetAll(const Point2& start);
	//移動範囲の検索
	void findSearchRange(const Point2& start, float cost);
	//目標地点の追加
	void AddTarget(const Point2& target);
	void AddTargets(const std::vector<Point2>& targets);
	//ノードの取得
	NodePtr operator [](const Point2& position) const;
	//検索パスノードの作成
	std::vector<NodePtr> CreatePath(const Point2& target) const;

private:
	//経路探索関数テンプレート
	template <typename Grid, typename List, typename Node>
	static std::vector<Node> FindPath(Grid& grid, List list, const Node& start)
	{
		list.Start(start);
		while (!list.IsEmpty())
		{
			list.Pop();
			if (list.IsGoal())
			{
				return grid.createPath(list.GetFront());
			}
			grid.neighbors(list.GetFront(), [&](const Node& node) {list.Push(node); });
			//grid.draw();//デバッグ表示
		}
		return std::vector<Node>();
	}

	//経路探索関数テンプレート
	template <typename Grid, typename List, typename Node>
	std::vector<std::vector<Node>> FindPathAllTarget(Grid& grid, List list, const Node& start)
	{
		std::vector<std::vector<Node>> result;
		list.Start(start);
		int num = 0;
		while (!list.IsEmpty())
		{
			list.Pop();
			if (list.IsGoal())
			{
				result.push_back(grid.createPath(list.GetFront()));
				num++;
				//全てのターゲットまでの道を入れたら
				if (targetNum <= num)
					break;
			}
			grid.neighbors(list.GetFront(), [&](const Node& node) {list.Push(node); });
			//grid.draw();//デバッグ表示
		}
		return result;
	}


private:
	//パス検索用格子ノード
	NodeGrid m_grid;

	int targetNum;
};