#pragma once
#include <array>
#include <cassert>
#include <functional>
#include <vector>
#include <string>
#include <iostream>
#include "../Node/Node/NodePtr.h"
#include "FieldMap.h"

// パス検索用格子ノード
class NodeGrid
{
public:
	// コンストラクタ
	explicit NodeGrid(FieldMap& map);
	
	// ノードの取得
	NodePtr operator [] (const Point2& position) const;

	// 近隣の未検索ノードを巡回
	void neighbors(const NodePtr& node, std::function<void(const NodePtr&)> fn) const;

	// 検索パスノードの作成
	std::vector<NodePtr> createPath(const NodePtr& goal) const;

private:
	// ノードの作成
	void createNode(FieldMap& map);

	// 未検索のノードか？
	bool opend(const Point2& position) const;

	// 格子の内側か？
	bool isInside(const Point2& position) const;

public:
	// 表示（デバッグ用）
	void draw() const;

private:
	// 幅
	int width_;
	// 高さ
	int height_;
	// 格子ノード
	std::vector<std::vector<NodePtr>> grid_;
};

