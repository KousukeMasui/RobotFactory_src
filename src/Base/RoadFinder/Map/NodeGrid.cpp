#include "NodeGrid.h"

// コンストラクタ

NodeGrid::NodeGrid(FieldMap& map) :
	width_(map.width()),
	height_(map.height())
{
	createNode(map);
}

NodePtr NodeGrid::operator [] (const Point2& position) const
{
	assert(isInside(position));
	return grid_[position.y][position.x];
}

// 近隣の未検索ノードを巡回
void NodeGrid::neighbors(const NodePtr & node, std::function<void(const NodePtr&)> fn) const
{
	static const std::array<Point2, 4> directions =
	{
		{ Point2(1, 0), Point2(-1, 0), Point2(0, 1),  Point2(0, -1) }
	};
	for (const auto& dir : directions)
	{
		if (opend(node->position() + dir))
			fn((*this)[node->position() + dir]);
	}
}

// 検索パスノードの作成

std::vector<NodePtr> NodeGrid::createPath(const NodePtr & goal) const
{
	std::vector<NodePtr> pathNodes;
	goal->backtrack([&](const Node& node) { pathNodes.push_back((*this)[node.position()]); });
	draw();	// デバッグ表示
	return pathNodes;
}

// ノードの作成

void NodeGrid::createNode(FieldMap & map)
{
	grid_.clear();
	Point2 position;
	for (position.y = 0; position.y < height_; ++position.y)
	{
		std::vector<NodePtr> row;
		for (position.x = 0; position.x < width_; ++position.x)
		{
			row.push_back(std::make_shared<Node>(position, map[position]));
		}
		grid_.push_back(row);
	}
}

// 未検索のノードか？

bool NodeGrid::opend(const Point2 & position) const
{
	return isInside(position) && (*this)[position]->walkable() && !(*this)[position]->closed();
}

// 格子の内側か？

bool NodeGrid::isInside(const Point2 & position) const
{
	return (0 <= position.x) && (position.x < width_)
		&& (0 <= position.y) && (position.y < height_);
}

// 表示（デバッグ用）

void NodeGrid::draw() const
{
	Point2 position;
	for (position.y = 0; position.y < height_; ++position.y)
	{
		for (position.x = 0; position.x < width_; ++position.x)
		{
			std::cout << (*this)[position]->to_string();
		}
		std::cout << "\n";
	}
	std::cout << "\n";
}
