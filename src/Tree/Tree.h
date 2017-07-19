#pragma once

class TreeNode;
#include<string>
#include<memory>
class Tree
{
public:
	Tree();
	~Tree();
	void SetRoot(std::shared_ptr<TreeNode> root);
	void Update(float deltaTime);

	int ID() const;

private:
	//一番下の階層のノード(葉)を探す
	std::shared_ptr<TreeNode> SearchLeaf();
	void Change();//ノードの変更
private:
	//現在のノード
	std::shared_ptr<TreeNode> m_nowNode;
	//根っこになる一番上のノード
	std::shared_ptr<TreeNode> m_root;
};