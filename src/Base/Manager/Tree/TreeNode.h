#pragma once

#include<memory>
#include<vector>
#include<functional>

class TreeNode
{
public:
	//コンストラクタ
	explicit TreeNode(int nodeID);
	//デフォルトコンストラクタ
	~TreeNode();

	virtual void Start() = 0;//初期化

	virtual void Update(float deltaTime) = 0;
	virtual void End() = 0;//終了
	bool IsEnd();//終わるときにtrue
	void AddChild(std::shared_ptr<TreeNode> child);

	//親ノードから自分に繋がるかのbool
	virtual bool Branch() = 0;

	//この下のノードを返す。
	std::shared_ptr<TreeNode> NextNode();

	int ID() const;
protected:
	//これに複数のノードを入れていく。　現在はノードの削除をすることは想定していない。
	//自分の子ノード
	std::vector<std::shared_ptr<TreeNode>> m_childNodes;
	const int m_nodeID;
	bool m_isEnd;
};