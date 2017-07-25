#include "InputManager.h"
#include"GamePad/DirectInput/DirectInput.h"
InputManager::InputManager():
	m_keyBoard()
{
	Initialize();
}
InputManager::~InputManager()
{
}
void InputManager::AddGamePad(const std::shared_ptr<GamePad>& gamePad)
{
	if(GetJoypadNum() >= gamePad->PadID())//Œq‚ª‚Á‚Ä‚¢‚é”‚æ‚è‘å‚«‚¢id‚Ìê‡
		m_gamePads[gamePad->PadID()] = gamePad;
}

void InputManager::Update()
{
	for (auto padItr = m_gamePads.begin(); padItr != m_gamePads.end(); padItr++)
		padItr->second->Update();

	m_keyBoard.Update();
}

bool InputManager::GetAction(KeyAction key, int padID)
{
	return m_keyAction[key](padID);
}

std::shared_ptr<GamePad> InputManager::GetGamePad(int padID) const
{
	return m_gamePads.at(padID);
}

MyVector3 InputManager::GetLeftVelocity(int padID) const
{
	if (m_gamePads.size() > 0)//“o˜^‚µ‚½ƒQ[ƒ€ƒpƒbƒh‚ª‚ ‚éê‡
		return m_gamePads.at(padID)->GetLeftStick3D();

	return m_keyBoard.GetVelocity();
}

MyVector2 InputManager::GetRightVelocity(int padID) const
{
	if (m_gamePads.size() > 0)//“o˜^‚µ‚½ƒQ[ƒ€ƒpƒbƒh‚ª‚ ‚éê‡
		return m_gamePads.at(padID)->GetRightStick();

	return m_keyBoard.GetArrowVelocity();//–îˆóƒL[
}

const KeyBoard & InputManager::GetKeyBoard()
{
	return m_keyBoard;
}

InputManager & InputManager::GetInstance()
{
	static InputManager inst;
	return inst;
}

void InputManager::Initialize()
{
	m_keyAction[KeyAction::Attack] = [&](int padID) {
		return m_keyBoard.IsKeyBoadDown(KEY_INPUT_RETURN) || (m_gamePads.count(padID) >0 &&m_gamePads[padID]->IsEnter(JC_PS101USV_ID::CIRCLE));};
	m_keyAction[KeyAction::Avoid] = [&](int padID) {
		return m_keyBoard.IsKeyBoadDown(KEY_INPUT_RSHIFT) || (m_gamePads.count(padID) >0 && m_gamePads[padID]->IsEnter(JC_PS101USV_ID::CROSS)); };
}