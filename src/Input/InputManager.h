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
//入力管理クラス 
class InputManager
{
public:
	InputManager();
	~InputManager();
	//追加
	void AddGamePad(const std::shared_ptr<GamePad>& gamePad);
	//更新
	void Update();
	//インプット判定
	bool GetAction(KeyAction key, int padID = 1);

	std::shared_ptr<GamePad> GetGamePad(int padID = 1) const;

	MyVector3 GetLeftVelocity(int padID = 1) const;
	MyVector2 GetRightVelocity(int padID = 1) const;

	const KeyBoard& GetKeyBoard();
public:
	static InputManager& GetInstance();
private:
	//初期化
	void Initialize();
private:
	//ゲームパッド
	std::map<int,std::shared_ptr<GamePad>> m_gamePads;
	KeyBoard m_keyBoard;
	//コマンド
	std::map<KeyAction, std::function<bool(int padID)>> m_keyAction;
};