#include "DxLib.h"
#include"Base/VectorUtility/VectorUtility.h"
// WinMain�֐�
int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nCmdShow)
{
	int FontHandle;

	// �c�w���C�u�����̏�����
	if (DxLib_Init() == -1) return 0;
	ChangeWindowMode(true);

	// �c�w�t�H���g�f�[�^�t�@�C����ǂݍ��݁A�t�H���g�n���h����ϐ� FontHandle �ɕۑ�����
	FontHandle = LoadFontDataToHandle("res/Texture/Font/TestFont.dft", 1);

	// �쐬�����t�H���g�ŉ�ʍ���Ɂw�g�����������I�I�x�Ɣ��F�̕������`�悷��
	//DrawStringToHandle(0, 0, "HP", GetColor(255, 255, 255), FontHandle);

	// ���ɕW���t�H���g�f�[�^�ŉ�ʂɁw�n�j�H�x�Ƃ����������`�悷��
	//DrawString(0, 50, "�n�j�H", GetColor(255, 128, 100));

	// �L�[���͂�҂�
	WaitKey();

	// �쐬�����t�H���g�f�[�^���폜����
	DeleteFontToHandle(FontHandle);

	// �c�w���C�u�����̏I��
	DxLib_End();

	// �\�t�g�̏I��
	return 0;
}