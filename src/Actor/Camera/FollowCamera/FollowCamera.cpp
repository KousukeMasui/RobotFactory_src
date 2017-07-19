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
	//target���X�V
	m_target = m_getPositionFunc();
	//��]����
	CameraRotate(Mouse::GetInstance().Velocity() / 10.0f);
	//�^�[�Q�b�g�̈ʒu�ɃJ������ݒ�
	CameraSet();
}

void FollowCamera::SetTarget(std::function<MyVector3()> getPositionFunc)
{
	m_getPositionFunc = getPositionFunc;
}
