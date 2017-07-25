#include "GamePad.h"

GamePad::GamePad(int padID, const MyVector2& clamp):
	m_padID(padID),
	m_stickClamp(clamp)
{
}

GamePad::~GamePad()
{
}

MyVector3 GamePad::GetLeftStick3D() const
{
	MyVector2 leftStick = GetLeftStick();
	return MyVector3(leftStick.x,0,leftStick.y);
}

MyVector3 GamePad::GetRightStick3D() const
{
	MyVector2 rightStick = GetRightStick();
	return MyVector3(rightStick.x, 0, rightStick.y);
}

int GamePad::PadID() const
{
	return m_padID;
}

MyVector2 GamePad::StickNormalize(const MyVector2 & stick) const
{
	MyVector2 result;
	//各軸の値を1.0f以下に修正してvelocity化
	if (stick.x < 0.0f)
		result.x = stick.x / m_stickClamp.x;
	else result.x = stick.x / m_stickClamp.y;
	if (stick.y < 0.0f)
		result.y = stick.y / m_stickClamp.x;
	else result.y = stick.y / m_stickClamp.y;

	//ベクトルが1以上なら正規化
	if (result.Length() >= 1.0f)
		result.Normalize();

	return result;
}
