#pragma once
#include"SelectCursor.h"
//徐々に追従
class LerpCursor : public SelectCursor
{
public:
	explicit LerpCursor(const MyVector3& position);
	~LerpCursor();

	void OnUpdate(float deltaTime) override;
	void SetPosition(const MyVector3& position) override;


private:
	const float m_speed;//移動速度
	MyVector3 m_targetPosition;
};