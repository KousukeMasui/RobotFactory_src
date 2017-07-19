#pragma once
#include"../Node/Node/NodePtr.h"
#include"../Node/NodePriorityQueue/NodePriorityQueue.h"
class AstarOpenList
{
public:
	//コンストラクタ
	explicit AstarOpenList(const NodePtr& target);

	//検索開始
	void Start(const NodePtr& start);

	//空か?
	bool IsEmpty();

	//ノードの取得
	void Pop();

	//先頭のノードを取得
	NodePtr GetFront() const;
	//ノードの追加
	void Push(const NodePtr& node);

	//目的地のノードに到達したか
	bool IsGoal() const;



private:
	//先頭のノード
	NodePtr			m_front;
	//目的地のノード
	NodePtr			m_target;
	//優先順位付きキュー
	NodePriorityQueue m_queue;
};