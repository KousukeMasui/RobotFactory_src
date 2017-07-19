#include"Input.h"
#include<DxLib.h>

Input::Input() {
	for (int index = 0; index < Max_Key_Num; ++index) {
		/*　キーボード配列の初期化　　*/
		curKeys[index] = 0;
		preKeys[index] = 0;
	}
	RegistFunc();
	PadInitialize();
}

Input::~Input() {
}

void Input::PadInitialize() {
	int padNum = GetJoypadNum();
	if (padNum == 0) return;
	//パッド1の接続設定 初期化
	GetJoypadXInputState(DX_INPUT_PAD1, &xInput);
}

void Input::RegistFunc() {
	//シャットダウン
	actionFunc[0] = [&](void)->bool {return IsKeyBoadState(KEY_INPUT_ESCAPE); };
	actionFunc[1] = [&](void)->bool {return IsGamePadState(XINPUT_BUTTON_BACK); };
}

Input & Input::GetInstance() {
	static Input instance;
	return instance;
}

bool Input::GetAction(KeyAction action) {
	return actionFunc[static_cast<int>(action)]();
}

void Input::Update() {
	//移し替えのメソッド
	preKeys.swap(curKeys);
	//現在のキーをcurKeysに入れてる
	GetHitKeyStateAll(curKeys.data());

	//パッド入力更新
	XBState = xInput;
	GetJoypadXInputState(DX_INPUT_PAD1, &xInput);
	SetJoypadDeadZone(DX_INPUT_PAD1, 0.35f);
	//軽くなるかも？
	ClearInputCharBuf();
}

/*　キーボード関係　*/
bool Input::IsKeyBoadUp(int key) {
	bool keyState = false;
	if (!curKeys[key] && preKeys[key])
		keyState = true;

	return keyState;
}

bool Input::IsKeyBoadDown(int key) {
	bool keyState = false;
	if (curKeys[key] && !preKeys[key])
		keyState = true;

	return keyState;
}

bool Input::IsKeyBoadState(int key) {
	bool keyState = false;
	if (curKeys[key] && preKeys[key])
		keyState = true;

	return keyState;
}

/*　ゲームパッド関係　*/
bool Input::IsGamePadUp(int pad) {
	bool padState = false;
	if (!xInput.Buttons[pad] && XBState.Buttons[pad])
		padState = true;

	return padState;
}

bool Input::IsGamePadDown(int pad) {
	bool padState = false;
	if (xInput.Buttons[pad] && !XBState.Buttons[pad])
		padState = true;

	return padState;
}

bool Input::IsGamePadState(int pad) {
	bool padState = false;
	if (xInput.Buttons[pad])
		padState = true;

	return padState;
}

MyVector3 Input::GetVelocity() {
	//プレイヤーの移動量
	MyVector3 velocity = MyVector3(0.0f, 0.0f, 0.0f);

	if (curKeys[KEY_INPUT_W])
		velocity.z += -1.0f;
	if (curKeys[KEY_INPUT_A])
		velocity.x += 1.0f;
	if (curKeys[KEY_INPUT_S])
		velocity.z += 1.0f;
	if (curKeys[KEY_INPUT_D])
		velocity.x += -1.0f;

	//斜めの正規化
	if (velocity.Length() != 0.0f)
		velocity.Normalize();

	return velocity;
}

MyVector2 Input::GetStickAngle() {
	//パッド1のスティック情報初期化
	GetJoypadXInputState(DX_INPUT_PAD1, &stick);
	MyVector2 velocity = MyVector2(0.0f, 0.0f);
	xStick = stick.ThumbLX;  //左スティックのx軸の値
	yStick = stick.ThumbLY;  //左スティックのy軸の値
	xStick = MyMath::Clamp(xStick, -30000, 30000);  //x軸の値の補正
	yStick = MyMath::Clamp(yStick, -30000, 30000);  //y軸の値の補正
	
	if ((xStick <= 5000) && (xStick >= -5000))   //x軸の微妙な傾きの補正
		xStick = 0;
	if ((yStick <= 5000) && (yStick >= -5000))   //y軸の微妙な傾きの補正
		yStick = 0;

	//各軸の値を1.0f以下に修正してvelocity化
	velocity = MyVector2(xStick / 30000, yStick / 30000);
	return velocity;
}

void Input::Draw() {
	DrawFormatString(100, 50, GetColor(255, 255, 255), "x = %.1f : y = %.1f", xStick, yStick);
}