#include"MyGame.h"
#include<DxLib.h>
#include"Math/Vector/MyVector3.h"
#include"Scene/Base/Scene.h"
#include"Scene/LoadScene/LoadScene.h"
#include"Scene/Title/TitleScene.h"
#include"Scene/GamePlay/GamePlayScene.h"
#include"Scene/Result/ResultScene.h"
#include"Screen/Screen.h"

#include"World\World.h"
#include"Input/Mouse/Mouse.h"
#include"Loader/Loader.h"
// EffekseerForDXLib.h���C���N���[�h���܂��B
#include "EffekseerForDXLib.h"
#include"EffekseerRendererDX9.h"

MyGame::MyGame(const char* windowName, bool isFullScreen):
	m_isEnd(false),
	m_fps(FPS(60.0f)),
	m_isWin(false),
	m_sceneManager()
{
	//SetOutApplicationLogValidFlag(false);
	SetMainWindowText(windowName);//�E�C���h�E�̖��O��ύX
	SetGraphMode(Screen::SCREEN_SIZE.x, Screen::SCREEN_SIZE.y, 16);//�X�N���[���T�C�Y��ݒ�
	ChangeWindowMode(!isFullScreen);//�t���X�N���[���ƃE�C���h�E�̐؂�ւ�

}
int MyGame::Run()
{
	// DirectX9���g�p����悤�ɂ���B
	// Effekseer���g�p����ɂ͕K���ݒ肷��B
	if (SetUseDirect3DVersion(DX_DIRECT3D_9) == -1)
	{
		return -1;
	}
	// �t���X�N���[���E�C���h�E�̐؂�ւ��Ń��\�[�X��������̂�h���B
	// Effekseer���g�p����ꍇ�͕K���ݒ肷��B
	SetChangeScreenModeGraphicsSystemResetFlag(FALSE);
	//�������Ɏ��s������
	if (DxLib_Init() == -1)
	{
		//�G���[�Ń��^�[��
		return -1;
	}

	if (!Initialize())//�������Ɏ��s�����ꍇ
	{
		DxLib_End();//dxlib���I��
		Effkseer_End();
		return -1;//�G���[���^�[��
	}

	SetDrawScreen(DX_SCREEN_BACK);

	//while( ����ʂ�\��ʂɔ��f,��ʃN���A )
	while (ScreenFlip() == 0 && ProcessMessage() == 0 && ClearDrawScreen() == 0 && !CheckHitKey(KEY_INPUT_ESCAPE))
	{
		Update(m_fps.GetFrameTime());
		Draw();
		if (m_isEnd)
		{
			break;
		}
	}

	End();
	Effkseer_End();
	DxLib_End();//�I������
	return 0;//�I��
}

bool MyGame::EffekseerInit()
{
	// Effekseer������������B
	// �����ɂ͉�ʂɕ\������ő�p�[�e�B�N������ݒ肷��B
	if (Effkseer_Init(2000) == -1)
	{
		DxLib_End();
		return false;
	}
	// DX���C�u�����̃f�o�C�X���X�g�������̃R�[���o�b�N��ݒ肷��B
	// �E�C���h�E�ƃt���X�N���[���̐؂�ւ�����������ꍇ�͕K�����s����B
	Effekseer_SetGraphicsDeviceLostCallbackFunctions();


	Effekseer_Set2DSetting(Screen::SCREEN_SIZE.x, Screen::SCREEN_SIZE.y);
	return true;
}

bool MyGame::Initialize()
{
	//�G�t�F�N�g�̏������Ɏ��s�����ꍇ return
	if (!EffekseerInit()) return false;

	Mouse::GetInstance().Initialize();
	Loader::GetInstance().Initialize();
	SetBackgroundColor(0, 0, 255);
	//���[���h����
	m_world = std::make_shared<World>();
	m_sceneManager.Initialize();
	m_sceneManager.Add(Scene::Load, std::make_shared<LoadScene>());
	m_sceneManager.Add(Scene::Title, std::make_shared<TitleScene>(m_world));
	m_sceneManager.Add(Scene::GamePlay, std::make_shared<GamePlayScene>(m_world,m_isWin));
	m_sceneManager.Add(Scene::Result, std::make_shared<ResultScene>(m_world,m_isWin));

	m_sceneManager.Change(Scene::Load);

	return true;
}
void MyGame::Update(float deltaTime)
{
	m_fps.Update();
	Mouse::GetInstance().Update(deltaTime);
	m_sceneManager.Update(deltaTime);
}
void MyGame::Draw()
{
	m_sceneManager.Draw();
	Mouse::GetInstance().Draw();
	//m_fps.Draw();
}
void MyGame::End()
{
}
