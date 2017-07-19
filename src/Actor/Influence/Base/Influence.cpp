#include "Influence.h"
#include"World/World.h"
Influence::Influence(IWorld & world, InfluenceID id):
	m_world(world),
	m_influenceID(id)
{
}

Influence::~Influence()
{
}

UnitPtrs Influence::GetUnits()
{
	return m_world.GetGameManager().GetUnitManager().GetFunction(m_influenceID, 
		[](const Unit& unit) {return !unit.IsDead(); });//����ł��Ȃ����j�b�g��S�Ď擾
}
