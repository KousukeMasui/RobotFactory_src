#pragma once
#include"SelectCursor.h"
//���X�ɒǏ]
class LerpCursor : public SelectCursor
{
public:
	explicit LerpCursor(const MyVector3& position);
	~LerpCursor();

	void OnUpdate(float deltaTime) override;
	void SetPosition(const MyVector3& position) override;


private:
	const float m_speed;//�ړ����x
	MyVector3 m_targetPosition;
};