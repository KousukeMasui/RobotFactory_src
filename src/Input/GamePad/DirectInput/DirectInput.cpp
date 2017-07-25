#include "DirectInput.h"

DirectInput::DirectInput(int padID):
	GamePad(padID,MyVector2(1000,1000))
{
}

DirectInput::~DirectInput()
{
}

void DirectInput::Update()
{
	m_prevState = m_currentState;
	GetJoypadDirectInputState(m_padID, &m_currentState);
}

MyVector2 DirectInput::GetLeftStick() const
{
	return StickNormalize(MyVector2(-m_currentState.X, m_currentState.Y));
}

MyVector2 DirectInput::GetRightStick() const
{
	return StickNormalize(MyVector2(m_currentState.Z, m_currentState.Rz));
}

bool DirectInput::IsEnter(int buttonID) const
{
	return m_currentState.Buttons[buttonID] == 128 && m_prevState.Buttons[buttonID] != 128;
}

bool DirectInput::IsState(int buttonID) const
{
	return m_currentState.Buttons[buttonID] == 128 && m_prevState.Buttons[buttonID] == 128;
}

bool DirectInput::IsExit(int buttonID) const
{
	return m_currentState.Buttons[buttonID] != 128 && m_prevState.Buttons[buttonID] == 128;
}
