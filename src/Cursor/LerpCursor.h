#pragma once
#include"SelectCursor.h"
//™X‚É’Ç]
class LerpCursor : public SelectCursor
{
public:
	explicit LerpCursor(const MyVector3& position);
	~LerpCursor();

	void OnUpdate(float deltaTime) override;
	void SetPosition(const MyVector3& position) override;


private:
	const float m_speed;//ˆÚ“®‘¬“x
	MyVector3 m_targetPosition;
};