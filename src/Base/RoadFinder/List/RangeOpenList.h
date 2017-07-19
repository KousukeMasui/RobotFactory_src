#pragma once
#include"../Node/Node/NodePtr.h"
#include"../Node/NodePriorityQueue/NodePriorityQueue.h"
//範囲検索オープンリスト
class RangeOpenList
{
public:
	//コンストラクタ
	explicit RangeOpenList(float cost);
	//検索開始
	void Start(const NodePtr& start);
	//空か?
	bool IsEmpty() const;

	//ノードの取得
	void Pop();
	//先頭ノードの取得
	NodePtr GetFront() const;

	//ノードの追加
	void Push(const NodePtr& node);

	bool IsGoal() const;

private:
	NodePtr				m_front;
	//移動コスト
	float				m_cost;
	//優先順位付きキュー
	NodePriorityQueue	m_queue;
};