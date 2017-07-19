#include "UnitAINode.h"
#include"../../Unit.h"
UnitAINode::UnitAINode(Unit & unit, UnitNodeID nodeID) :
	TreeNode((int)nodeID),
	m_unit(unit)
{
}

UnitAINode::~UnitAINode()
{
}

void UnitAINode::Update(float deltaTime)
{
	//hp��0��float�̌v�Z�덷�ȉ��������玀�񂾂̂Ō��݂̃m�[�h���I��������
	m_isEnd = m_unit.GetStatus().hp <= FLT_EPSILON || SetIsEnd();

	OnUpdate(deltaTime);
}
