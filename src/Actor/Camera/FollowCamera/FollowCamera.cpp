#include "FollowCamera.h"
#include"Input\Mouse\Mouse.h"
#include"Math/Converter.h"
FollowCamera::FollowCamera():
	Camera(MyVector3(Converter::DegToRad(-60.0f), Converter::DegToRad(90.0f),0.0f))
{
}

FollowCamera::~FollowCamera()
{
}

void FollowCamera::Update(float deltaTime)
{
	//targetを更新
	m_target = m_getPositionFunc();
	//回転処理
	CameraRotate(Mouse::GetInstance().Velocity() / 10.0f);
	//ターゲットの位置にカメラを設定
	CameraSet();
}

void FollowCamera::SetTarget(std::function<MyVector3()> getPositionFunc)
{
	m_getPositionFunc = getPositionFunc;
}
