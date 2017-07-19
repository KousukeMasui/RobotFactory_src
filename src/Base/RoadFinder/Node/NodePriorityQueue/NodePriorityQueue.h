#pragma once
#include"../Node/NodePtr.h"
#include "PriorityQueue.h"
//ノード用
class NodePriorityQueue
{
public:
	//コンストラクタ
	NodePriorityQueue();
	//空か?
	bool IsEmpty() const;
	//ノードの取得
	NodePtr Pop();
	//ノードの追加
	void Push(const NodePtr& node);

	void Clear();
private:
	//ノードの比較関数
	static bool Comp(const NodePtr& n1, const NodePtr& n2);
private:
	//ノード比較関数型
	typedef bool(*CompNode)(const NodePtr&, const NodePtr&);
	//優先順位付きキュー
	PriorityQueue<NodePtr, CompNode> m_queue;
};