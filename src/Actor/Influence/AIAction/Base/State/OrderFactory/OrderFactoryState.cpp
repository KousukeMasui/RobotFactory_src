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
	MyVector3 target = m_factory->GetParam().Position();

	//�o�H�T��
	FindRoot();
	//�^�������i�񂾏ꍇ�A�H��ɂԂ��邩����
	//for (auto factory : factorys)
	//{
	//	m_isStraight = true;
	//	if (factory == m_factory) continue;//�ړI�̍H��͏��O

	//	if (factory->IsCollide(capsule))
	//	{
	//		m_isStraight = false;
	//		break;
	//	}
	//}

	m_target = target;
	
}

void OrderFactoryState::Update(float deltaTime)
{
	m_cursor->Update(m_target, deltaTime);
}

void OrderFactoryState::Draw() const
{
}

void OrderFactoryState::End()
{
	if (m_root.empty())
		m_unit->Message((int)UnitMessageID::ROOT, &m_cursor->Position());
	else
		m_unit->Message((int)UnitMessageID::ROOT_VECTOR, &m_root);
}

int OrderFactoryState::Next() const
{
	return (int)CursorStateID::TO_UNIT;
}

bool OrderFactoryState::IsEnd() const
{
	return m_cursor->IsCollide(m_factory);
}

void OrderFactoryState::FindRoot()
{
	PathFinder f(m_world.GetFieldMap());
	auto nonePoints = m_world.GetMetaAI().GetUnitPoints(*m_unit);
	for (auto p : nonePoints)
		f[p]->SetWalkable(false);//�ړ��s�Ƃ��Ĉ���
	auto ps = VectorUtility::NonObjects<Point2>(m_factory->GetPoints(), nonePoints);

	f.AddTargets(ps);
	m_root =  PathFind3DUtility::ToRoad(f.FindMultiTarget(PathFind3DUtility::ToNodePoint2(m_unit->Position(),f)),f);
}
