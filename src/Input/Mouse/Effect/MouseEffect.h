#pragma once
#include"Math/Vector/MyVector2.h"
class MouseEffect
{
public:
	MouseEffect();
	~MouseEffect();

	void Update(float deltaTime);
	void Draw() const;

	void Create(const MyVector2& position);

private:
	int m_effectHandle;
	float m_timer;
	const float m_createTime;
};