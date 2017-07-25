#include "Tree.h"
#include"TreeNode.h"
Tree::Tree()
{
}
Tree::~Tree()
{
}
void Tree::SetRoot(std::shared_ptr<TreeNode> root)
{
	m_root = root;
	m_nowNode = SearchLeaf();
	m_nowNode->Start();
}

void Tree::Update(float deltaTime)
{
	if (m_nowNode->IsEnd()) Change();
	m_nowNode->Update(deltaTime);
}

std::shared_ptr<TreeNode> Tree::SearchLeaf()
{
	std::shared_ptr<TreeNode> result = m_root;
	std::shared_ptr<TreeNode> prevResult = nullptr;
	do
	{
		prevResult = result;
		result = result->NextNode();
	} while (result != nullptr);//子がいない場合、あるいは枝の条件を全て満たせない場合

	return prevResult;
}

void Tree::Change()
{
	m_nowNode->End();//終了処理
	m_nowNode = SearchLeaf();//末葉を検索
	m_nowNode->Start();//開始処理
}

int Tree::ID() const
{
	return m_nowNode->ID();
}