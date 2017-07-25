#include "TreeNode.h"

TreeNode::TreeNode(int nodeID):
	m_childNodes(),
	m_nodeID(nodeID),
	m_isEnd(false)
{
}

TreeNode::~TreeNode()
{
}

bool TreeNode::IsEnd()
{
	return m_isEnd;
}

//�q�̐߂Ƃ��̐߂܂ł̎}��ǉ�����֐�
void TreeNode::AddChild(std::shared_ptr<TreeNode> child)
{
	m_childNodes.push_back(child);
}

std::shared_ptr<TreeNode> TreeNode::NextNode()
{
	std::shared_ptr<TreeNode> result = nullptr;
	for (auto child : m_childNodes)
	{
		//�}�̏����𖞂����Ă�����
		if (child->Branch())
		{
			result = child;
			break;
		}
	}
	return result;
}

int TreeNode::ID() const
{
	return m_nodeID;
}
