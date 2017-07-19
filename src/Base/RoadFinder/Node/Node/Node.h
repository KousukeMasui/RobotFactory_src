#pragma once
#include "Math/Point2/Point2.h"
#include <functional>

// 検索ノード
class Node
{
public:
	// コンストラクタ
	Node(const Point2& position, int index);
	int Index();
	// 座標の取得
	Point2 position() const;

	//合計コストの取得
	float Total() const;

	// 更新する
	void update(Node& parent, float h = 0.0f);

	//検索中にする
	void Open();
	//検索中ノードか
	bool IsOpened();

	bool IsTarget() const;

	void TargetSet();
	// 検索終了ノードか？
	bool closed() const;

	// 移動可能か？
	bool walkable() const;

	// 検索終了にする
	void close();
	//移動可能か設定する
	void SetWalkable(bool isWalkable);

	bool IsUpdate(const Node& parent) const;

	// 目的地からスタート地点までさかのぼる
	void backtrack(std::function<void(Node& node)> f);

	float Distance(const Node& target) const;

	//比較関数
	bool operator < (const Node& other) const;

	// 文字列化（デバッグ用）
	std::string to_string() const;

private:
	Point2		m_position;		// 座標
	bool		m_isWalk;		// 移動しているか？
	float		m_cost;
	Node*		m_parent;		// 親座標
	bool		m_isOpened;
	bool		m_isClose;		// 検索が終了しているか？
	bool		m_isTarget;		//目標地点か？
	float		m_totalCost;
	float		m_estimate;//ゴールまでの見積もり
	bool		m_isPath;			// パス内のノードか？（デバッグ用）
	int m_index;
};


