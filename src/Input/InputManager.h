#pragma once
#include"GamePad\GamePad.h"
#include"KeyBoard/KeyBoard.h"
#include<memory>
#include<map>
#include<functional>
enum class KeyAction {
	GamePadShutDown = 0,
	Attack,
	Avoid,
	NONE
};
//���͊Ǘ��N���X 
class InputManager
{
public:
	InputManager();
	~InputManager();
	//�ǉ�
	void AddGamePad(const std::shared_ptr<GamePad>& gamePad);
	//�X�V
	void Update();
	//�C���v�b�g����
	bool GetAction(KeyAction key, int padID = 1);

	std::shared_ptr<GamePad> GetGamePad(int padID = 1) const;

	MyVector3 GetLeftVelocity(int padID = 1) const;
	MyVector2 GetRightVelocity(int padID = 1) const;

	const KeyBoard& GetKeyBoard();
public:
	static InputManager& GetInstance();
private:
	//������
	void Initialize();
private:
	//�Q�[���p�b�h
	std::map<int,std::shared_ptr<GamePad>> m_gamePads;
	KeyBoard m_keyBoard;
	//�R�}���h
	std::map<KeyAction, std::function<bool(int padID)>> m_keyAction;
};