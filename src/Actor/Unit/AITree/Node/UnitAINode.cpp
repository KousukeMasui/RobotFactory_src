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
	//hpが0かfloatの計算誤差以下だったら死んだので現在のノードを終了させる
	m_isEnd = m_unit.GetStatus().hp <= FLT_EPSILON || SetIsEnd();

	OnUpdate(deltaTime);
}
