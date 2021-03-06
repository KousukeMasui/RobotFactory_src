#include "LiftObject.h"
#include"Actor\Unit\Unit.h"
#include<DxLib.h>
LiftObject::LiftObject(LIFT_ID id, const MyVector3& position):
	Object(position,MyMatrix4::Identity()),
	m_id(id),
	m_isLifted(false),
	m_isLiftEnd(false)
{
}

LiftObject::~LiftObject()
{
}
void LiftObject::LiftStart()
{
	m_isLifted = true;
}

void LiftObject::LiftEnd()
{
	m_isLifted = false;
	m_isLiftEnd = false;
}

void LiftObject::LiftUp(Unit & unit)
{
	//少し離れすぎなので後で修正
	//両手のボーンの間にする
	MyVector3 leftHandPos = unit.GetModel().GetBonePosition("R_Hand");
	MyVector3 rightHandPos = unit.GetModel().GetBonePosition("L_Hand");
	m_position = (leftHandPos + rightHandPos) / 2.0f;
	m_rotate = unit.Rotate();
}

//持ち上げが終わった時に動かす
void LiftObject::LiftUpEnd()
{
	m_isLiftEnd = true;
}

bool LiftObject::IsLiftStart() const
{
	return m_isLifted;
}

bool LiftObject::IsLiftEnd() const
{
	return m_isLiftEnd;
}

LIFT_ID LiftObject::GetID() const
{
	return m_id;
}
