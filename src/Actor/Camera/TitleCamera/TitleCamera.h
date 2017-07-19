#pragma once

#include"../Camera.h"
#include<vector>
class TitleCamera : public Camera
{
public:
	TitleCamera();
	~TitleCamera();

	virtual void Update(float deltaTime) override;

private:
	//�ړI�n�̔z��
	std::vector<MyVector3> m_points;
	//�ړI�n�ɒ��������̉�]�p�x
	std::vector<MyVector3> m_rads;

	//���݂̔z��̃C���f�b�N�X
	int m_index;
	//leap���l
	float m_lerp;
	//csv�̈ʒu
	const int m_pointStartCol;
	const int m_radStartCol;
};