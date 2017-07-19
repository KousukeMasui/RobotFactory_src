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

UnitPtr MouseSelect::Update(float deltaTime)
{
	auto line = Mouse::GetInstance().ToWorldLine();
	HitInfo hit;
	m_cursor.Update(CursorPosition(line, hit), deltaTime);

	return m_cursor.IsCollide(m_world, InfluenceID::PLAYER);
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
	//�n�ʃ��f���Ɠ����蔻����s��
	hit = m_world.GetField()->IsCollide(line);
	//���݂̃}�E�X�̐��Vector3���擾
	MyVector3 result = hit.hitPosition;

	return result;
}