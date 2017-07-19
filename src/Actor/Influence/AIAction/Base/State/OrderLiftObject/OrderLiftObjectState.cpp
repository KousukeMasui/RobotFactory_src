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
}

void OrderLiftObjectState::Update(float deltaTime)
{
	m_cursor->Update(m_lift->Position(), deltaTime);
}

void OrderLiftObjectState::Draw() const
{
}

void OrderLiftObjectState::End()
{
	//真っすぐ進んだ場合、ぶつかるか判定
	auto factorys = m_world.GetGameManager().GetFactoryManager().All();
	Capsule capsule(m_unit->Position(), m_lift->Position(), m_unit->GetSphere().m_radius);

	for (auto factory : factorys)
	{
		if (factory->IsCollide(capsule))
		{
			//経路探索して返す
			PathFinder f(m_world.GetFieldMap());
			m_unit->Message((int)UnitMessageID::ROOT_VECTOR, 
				&PathFind3DUtility::ToRoad(f.FindTarget(
					PathFind3DUtility::ToNodePoint2(m_unit->Position(),f),
					PathFind3DUtility::ToNodePoint2(m_lift->Position(),f)),f));
			return;

		}
	}//当たらない場合直進させる

	m_unit->Message((int)UnitMessageID::ROOT, &m_lift->Position());
}

int OrderLiftObjectState::Next() const
{
	return (int)CursorStateID::TO_UNIT;
}

bool OrderLiftObjectState::IsEnd() const
{
	return (m_lift->Position() - m_cursor->Position()).Length() <= m_cursor->GetSphere().m_radius;
}
