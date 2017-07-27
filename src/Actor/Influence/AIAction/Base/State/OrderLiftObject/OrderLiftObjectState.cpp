#include "OrderLiftObjectState.h"
#include"Cursor/LerpCursor.h"
#include"Actor\Unit\Unit.h"
#include"World/World.h"
#include"Base/RoadFinder/PathFinder.h"
#include"Base/RoadFinder/PathFind3DUtility.h"
#include"../../CursorStateID.h"
#include"Actor/Unit/Base/UnitMessageID.h"

#include"Actor/UnitFactory/UnitFactory.h"
OrderLiftObjectState::OrderLiftObjectState(IWorld& world, LerpCursor* cursor, const UnitPtr & orderUnit, const LiftObjectPtr& lift):
	CursorState(cursor,orderUnit),
	m_world(world),
	m_lift(lift)
{
}

OrderLiftObjectState::~OrderLiftObjectState()
{
}

void OrderLiftObjectState::Initialize()
{
	m_cursor->SetPosition(m_lift->Position());
}

void OrderLiftObjectState::Update(float deltaTime)
{
	m_cursor->Update(deltaTime);
}

void OrderLiftObjectState::Draw() const
{
}

void OrderLiftObjectState::End()
{
	m_world.GetGameManager().GetMetaAI().GetFind().PathFind(m_world.GetGameManager().GetMetaAI().GetFind().CreatePathFinder(),
		m_lift->Position(), m_unit->Agent());
}

int OrderLiftObjectState::Next() const
{
	return (int)CursorStateID::TO_UNIT;
}

bool OrderLiftObjectState::IsEnd() const
{
	return (m_lift->Position() - m_cursor->Position()).Length() <= m_cursor->GetSphere().m_radius;
}
