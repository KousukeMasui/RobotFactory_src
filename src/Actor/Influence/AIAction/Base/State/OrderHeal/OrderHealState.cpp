#include "OrderHealState.h"
#include"Actor/UnitFactory/UnitFactory.h"
#include"Actor/Unit/Unit.h"
#include"World/World.h"
#include"Base/RoadFinder/PathFinder.h"
#include"Base/RoadFinder/PathFind3DUtility.h"
#include"Actor/Unit/Base/UnitMessageID.h"
OrderHealState::OrderHealState(IWorld & world, LerpCursor * cursor, const UnitPtr & orderUnit, UnitFactory* factory):
	CursorState(cursor,orderUnit),
	m_world(world),
	m_factory(factory),
	m_line(m_unit->Position() + MyVector3(0,2,0), m_factory->GetParam().Position() + MyVector3(0, 2, 0))
{
}

OrderHealState::~OrderHealState()
{
}

void OrderHealState::Initialize()
{
	float t;
	m_targetPosition = m_factory->GetHeal().GetSphere().IsCollide(m_line,t).hitPosition;
	m_cursor->SetPosition(m_targetPosition);
}

void OrderHealState::Update(float deltaTime)
{
	m_cursor->Update(deltaTime);
}

void OrderHealState::Draw() const
{
}

void OrderHealState::End()
{
	auto factorys = m_world.GetGameManager().GetFactoryManager().All();
	for (auto factory : factorys)
	{
		if (m_factory == &*factory) continue;

		if (factory->IsCollide(m_line).isHit)
		{
			m_world.GetGameManager().GetMetaAI().GetFind().PathFind(m_world.GetGameManager().GetMetaAI().GetFind().CreatePathFinder(),
				m_targetPosition, m_unit->Agent());
			return;
		}
	}
	m_unit->Agent().SetRoot(m_cursor->Position());
}

int OrderHealState::Next() const
{
	return 0;
}

bool OrderHealState::IsEnd() const
{
	return m_cursor->GetSphere().IsCollide(m_factory->GetHeal().GetSphere());
}
