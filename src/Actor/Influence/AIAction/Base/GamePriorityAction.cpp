#include "GamePriorityAction.h"
GamePriorityAction::GamePriorityAction(float priority, IWorld & world, InfluenceID id, LerpCursor * cursor, UnitPtrs& units):
	PriorityAction(priority),
	m_world(world),
	m_influenceID(id),
	m_cursor(cursor),
	m_units(units),
	m_distancePriority(10000.0f)
{
}

GamePriorityAction::~GamePriorityAction()
{
}