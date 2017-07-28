#include "MouseSelect.h"
#include"Input/Mouse/Mouse.h"
#include"World/World.h"
MouseSelect::MouseSelect(IWorld& world):
	m_world(world),
	m_cursor(MyVector3())
{
}

MouseSelect::~MouseSelect()
{
}

void MouseSelect::Update(float deltaTime)
{
	auto line = Mouse::GetInstance().ToWorldLine();
	HitInfo hit;
	m_cursor.SetPosition(CursorPosition(line, hit));
	m_cursor.Update(deltaTime);
}

UnitPtr MouseSelect::HitUnit() const
{
	auto unit = m_world.GetGameManager().GetMetaAI().Distance().NearUnit(m_cursor,
		m_world.GetGameManager().GetUnitManager().GetVector(InfluenceID::PLAYER));
	if (m_cursor.IsCollide(unit->GetSphere()))
		return unit;
	return nullptr;
}

FactoryPtr MouseSelect::HitFactory() const
{
	auto factory = m_world.GetGameManager().GetMetaAI().Distance().NearFactory(m_cursor,
		m_world.GetGameManager().GetFactoryManager().All());
	if (m_cursor.IsCollide(&*factory))
		return factory;
	return nullptr;
}

SelectCursor & MouseSelect::GetCursor()
{
	return m_cursor;
}

void MouseSelect::Draw() const
{
	m_cursor.Draw(Color(0.0f,0.0f,1.0f));
}

MyVector3 MouseSelect::CursorPosition(const Line3D & line, HitInfo & hit) const
{
	//地面モデルと当たり判定を行う
	hit = m_world.GetField()->IsCollide(line);
	//現在のマウスの先のVector3を取得
	MyVector3 result = hit.hitPosition;

	return result;
}