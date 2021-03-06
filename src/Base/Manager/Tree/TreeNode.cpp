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

//子の節とその節までの枝を追加する関数
void TreeNode::AddChild(std::shared_ptr<TreeNode> child)
{
	m_childNodes.push_back(child);
}

std::shared_ptr<TreeNode> TreeNode::NextNode()
{
	std::shared_ptr<TreeNode> result = nullptr;
	for (auto child : m_childNodes)
	{
		//枝の条件を満たしていたら
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
