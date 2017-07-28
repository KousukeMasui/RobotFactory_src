#include "Field.h"
#include"Resources.h"
#include"Loader\Loader.h"
#include"Math/Collision/Model/ModelCollision.h"
#include"Math/Matrix/MyMatrix4.h"
#include"Math/Converter.h"
#include"Input/InputManager.h"
Field::Field() :
	m_groundModel(MODEL_ID::GROUND,true,MyMatrix4::Scale(10.0f, 1.0f, 10.0f).SetPosition(MyVector3(800,0,800))),
	m_skyModel(MODEL_ID::SKYDOME,true,MyMatrix4::Scale(10.0f,10.0f,10.0f)),
	m_clampModel(MODEL_ID::CLAMP_FIELD,true, MyMatrix4::Translate(MyVector3(800, 0, 800))),
	testAddY(1.0f)
{
	m_groundModel.CollideSet(16, 16, 16);
}

Field::~Field()
{


}

void Field::Update(float deltaTime)
{
	if (InputManager::GetInstance().GetKeyBoard().IsKeyBoadState(KEY_INPUT_S)) {
		testAddY -= 0.01f;
	}
	if (InputManager::GetInstance().GetKeyBoard().IsKeyBoadState(KEY_INPUT_W)) {
		testAddY += 0.01f;
	}
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

MyVector3 Field::OnPosition(const MyVector3 & position)
{
	//à íuÇ©ÇÁècï˚å¸Ç…ìñÇΩÇËîªíË
	HitInfo hit = IsCollide(position + MyVector3(0, 500, 0), position - MyVector3(0, 500, 0));
	return hit.hitPosition + MyVector3(0, 7.44007587f,0.0f);
}
