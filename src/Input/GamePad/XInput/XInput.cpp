#include "XInput.h"

XInput::XInput(int padID):
	GamePad(padID,MyVector2(-SHRT_MIN,SHRT_MAX))
{
}

XInput::~XInput()
{
}

void XInput::Update()
{
	m_prevState = m_currentState;
	GetJoypadXInputState(m_padID, &m_currentState);
}

MyVector2 XInput::GetLeftStick() const
{
	return MyVector2();
}

MyVector2 XInput::GetRightStick() const
{
	return MyVector2();
}

bool XInput::IsEnter(int buttonID) const
{
	return false;
}

bool XInput::IsState(int buttonID) const
{
	return false;
}

bool XInput::IsExit(int buttonID) const
{
	return false;
}
