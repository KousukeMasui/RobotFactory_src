#pragma once

//�Ǐ]�J���� �ʒu�̎Q�ƃ|�C���^���擾���Ă���ɒǏ]����
#include"Actor\Camera\Camera.h"
#include<functional>
class FollowCamera : public Camera
{
public:
	explicit FollowCamera();
	~FollowCamera();

	void Update(float deltaTime) override;

	void SetTarget(std::function <MyVector3()> getPositionFunc);

private:
	//�ʒu���擾���郉���_��
	std::function <MyVector3()> m_getPositionFunc;
};