#include "Field.h"
#include"Resources.h"
#include"Loader\Loader.h"
#include"Math/Collision/Model/ModelCollision.h"
#include"Math/Matrix/MyMatrix4.h"
#include"Math/Converter.h"
#include"Input/Input.h"
Field::Field() :
	m_groundModel(MODEL_ID::GROUND,true,MyMatrix4::Scale(10.0f, 1.0f, 10.0f).SetPosition(MyVector3(800,0,800))),
	m_skyModel(MODEL_ID::SKYDOME,true,MyMatrix4::Scale(10.0f,10.0f,10.0f)),
	m_clampModel(MODEL_ID::CLAMP_FIELD,true, MyMatrix4::Translate(MyVector3(800, 0, 800)))
{
	m_groundModel.CollideSet(16, 16, 16);
}

Field::~Field()
{


}

void Field::Update(float deltaTime)
{
}

void Field::Draw()
{
	m_skyModel.Draw();
	m_groundModel.Draw();
	m_clampModel.Draw();
}

HitInfo Field::IsCollide(const Line3D & line)
{
	return ModelCollision::Model_Line3D(m_groundModel, line);
}

HitInfo Field::IsCollide(const MyVector3 & p1, const MyVector3 & p2)
{
	return ModelCollision::Model_Line3D(m_groundModel, p1, p2);
}
