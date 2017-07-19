#include "Node.h"
#include"Math/Point2/Point2.h"
// �R���X�g���N�^

 Node::Node(const Point2 & position, int index) :
	m_position(position),
	m_isWalk(index ==0),
	m_cost(1.0f),
	m_parent(nullptr),
	m_isOpened(false),
	m_isClose(false),
	m_isTarget(false),
	m_totalCost(0.0f),
	m_estimate(0.0f),
	m_isPath(false),
	 m_index(index)
{
}

 int Node::Index()
 {
	 return m_index;
 }

// ���W�̎擾

 Point2 Node::position() const
{
	return m_position;
}

//���v�R�X�g�̎擾

 float Node::Total() const
{
	return m_totalCost;
}

// �X�V����

 void Node::update(Node & parent, float h)
{
	m_totalCost = parent.m_totalCost + m_cost;
	m_estimate = m_totalCost + h;
	m_parent = &parent;
}

//�������ɂ���

 void Node::Open()
{
	m_isOpened = true;
}

//�������m�[�h��

 bool Node::IsOpened()
{
	return m_isOpened;
}

 bool Node::IsTarget() const
{
	return m_isTarget;
}

 void Node::TargetSet()
{
	m_isTarget = true;
}

// �����I���m�[�h���H

 bool Node::closed() const
{
	return m_isClose;
}

// �ړ��\���H

 bool Node::walkable() const
{
	return m_isWalk;
}

// �����I���ɂ���

 void Node::close()
{
	m_isClose = true;
}

 void Node::SetWalkable(bool isWalkable)
 {
	 m_isWalk = isWalkable;
 }
 bool Node::IsUpdate(const Node & parent) const
{
	if (!m_isOpened) return true;
	if ((parent.m_totalCost + m_cost) < m_totalCost) return true;
	return false;
}

// �ړI�n����X�^�[�g�n�_�܂ł����̂ڂ�

 void Node::backtrack(std::function<void(Node&node)> f)
{
	for (auto node = this; node != nullptr; node = node->m_parent)
	{
		f(*node);
		node->m_isPath = true;	// �f�o�b�O�p
	}
}

 float Node::Distance(const Node & target) const
{
	return m_position.Distance(target.m_position);
}

//��r�֐�
bool Node::operator < (const Node& other) const
{
	return m_estimate < other.m_estimate;
}

// �����񉻁i�f�o�b�O�p�j

 std::string Node::to_string() const
{
	if (!m_isWalk)	return "��";
	if (m_isPath)	return "��";
	if (m_isClose)	return "�~";
	if (m_isOpened)	return "��";
	if (m_isTarget) return "��";
	return	"�@";
}
