#include "OrderFactoryState.h"
#include"Cursor/LerpCursor.h"
#include"Actor/UnitFactory/UnitFactory.h"
#include"Actor/Unit/Unit.h"
#include"Math/Shapes/3D/Line/Line3D.h"
#include"Math/Shapes/3D/Capsule/Capsule.h"
#include"World/World.h"
#include"Base/RoadFinder/PathFinder.h"
#include"Base/RoadFinder/PathFind3DUtility.h"
#include"../../CursorStateID.h"
#include"Actor/Unit/Base/UnitMessageID.h"
#include"Base/VectorUtility/VectorUtility.h"
OrderFactoryState::OrderFactoryState(IWorld & world, LerpCursor * cursor, const UnitPtr & unit, UnitFactory* factory, InfluenceID influence):
	CursorState(cursor,unit),
	m_world(world),
	m_factory(factory),
	m_influence(influence),
	m_isStraight(true)
{
}

OrderFactoryState::~OrderFactoryState()
{
}

void OrderFactoryState::Initialize()
{
	m_root.clear();
	m_cursor->SetPosition(m_factory->GetParam().Position());
	
}

void OrderFactoryState::Update(float deltaTime)
{
	m_cursor->Update(deltaTime);
}

void OrderFactoryState::Draw() const
{
}

void OrderFactoryState::End()
{
	//�o�H�T��
	//FindRoot();

	auto nonePoints = m_world.GetGameManager().GetMetaAI().GetUnitPoints(*m_unit);
	auto targets = VectorUtility::NonObjects<Point2>(m_factory->GetPoints(), nonePoints);
	m_unit->Agent().StartFind(targets,nonePoints, false);

}

int OrderFactoryState::Next() const
{
	return (int)CursorStateID::TO_UNIT;
}

bool OrderFactoryState::IsEnd() const
{
	return m_cursor->IsCollide(m_factory);
}
