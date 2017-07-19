#include"Input.h"
#include<DxLib.h>

Input::Input() {
	for (int index = 0; index < Max_Key_Num; ++index) {
		/*�@�L�[�{�[�h�z��̏������@�@*/
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
	//�p�b�h1�̐ڑ��ݒ� ������
	GetJoypadXInputState(DX_INPUT_PAD1, &xInput);
}

void Input::RegistFunc() {
	//�V���b�g�_�E��
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
	//�ڂ��ւ��̃��\�b�h
	preKeys.swap(curKeys);
	//���݂̃L�[��curKeys�ɓ���Ă�
	GetHitKeyStateAll(curKeys.data());

	//�p�b�h���͍X�V
	XBState = xInput;
	GetJoypadXInputState(DX_INPUT_PAD1, &xInput);
	SetJoypadDeadZone(DX_INPUT_PAD1, 0.35f);
	//�y���Ȃ邩���H
	ClearInputCharBuf();
}

/*�@�L�[�{�[�h�֌W�@*/
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

/*�@�Q�[���p�b�h�֌W�@*/
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
	//�v���C���[�̈ړ���
	MyVector3 velocity = MyVector3(0.0f, 0.0f, 0.0f);

	if (curKeys[KEY_INPUT_W])
		velocity.z += -1.0f;
	if (curKeys[KEY_INPUT_A])
		velocity.x += 1.0f;
	if (curKeys[KEY_INPUT_S])
		velocity.z += 1.0f;
	if (curKeys[KEY_INPUT_D])
		velocity.x += -1.0f;

	//�΂߂̐��K��
	if (velocity.Length() != 0.0f)
		velocity.Normalize();

	return velocity;
}

MyVector2 Input::GetStickAngle() {
	//�p�b�h1�̃X�e�B�b�N��񏉊���
	GetJoypadXInputState(DX_INPUT_PAD1, &stick);
	MyVector2 velocity = MyVector2(0.0f, 0.0f);
	xStick = stick.ThumbLX;  //���X�e�B�b�N��x���̒l
	yStick = stick.ThumbLY;  //���X�e�B�b�N��y���̒l
	xStick = MyMath::Clamp(xStick, -30000, 30000);  //x���̒l�̕␳
	yStick = MyMath::Clamp(yStick, -30000, 30000);  //y���̒l�̕␳
	
	if ((xStick <= 5000) && (xStick >= -5000))   //x���̔����ȌX���̕␳
		xStick = 0;
	if ((yStick <= 5000) && (yStick >= -5000))   //y���̔����ȌX���̕␳
		yStick = 0;

	//�e���̒l��1.0f�ȉ��ɏC������velocity��
	velocity = MyVector2(xStick / 30000, yStick / 30000);
	return velocity;
}

void Input::Draw() {
	DrawFormatString(100, 50, GetColor(255, 255, 255), "x = %.1f : y = %.1f", xStick, yStick);
}