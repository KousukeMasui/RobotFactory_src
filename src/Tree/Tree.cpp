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
	} while (result != nullptr);//�q�����Ȃ��ꍇ�A���邢�͎}�̏�����S�Ė������Ȃ��ꍇ

	return prevResult;
}

void Tree::Change()
{
	m_nowNode->End();//�I������
	m_nowNode = SearchLeaf();//���t������
	m_nowNode->Start();//�J�n����
}

int Tree::ID() const
{
	return m_nowNode->ID();
}