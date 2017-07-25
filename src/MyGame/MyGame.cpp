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
// EffekseerForDXLib.hをインクルードします。
#include "EffekseerForDXLib.h"
#include"EffekseerRendererDX9.h"

MyGame::MyGame(const char* windowName, bool isFullScreen):
	m_isEnd(false),
	m_fps(FPS(60.0f)),
	m_isWin(false),
	m_sceneManager()
{
	//SetOutApplicationLogValidFlag(false);
	SetMainWindowText(windowName);//ウインドウの名前を変更
	SetGraphMode(Screen::SCREEN_SIZE.x, Screen::SCREEN_SIZE.y, 16);//スクリーンサイズを設定
	ChangeWindowMode(!isFullScreen);//フルスクリーンとウインドウの切り替え

}
int MyGame::Run()
{
	// DirectX9を使用するようにする。
	// Effekseerを使用するには必ず設定する。
	if (SetUseDirect3DVersion(DX_DIRECT3D_9) == -1)
	{
		return -1;
	}
	// フルスクリーンウインドウの切り替えでリソースが消えるのを防ぐ。
	// Effekseerを使用する場合は必ず設定する。
	SetChangeScreenModeGraphicsSystemResetFlag(FALSE);
	//初期化に失敗したら
	if (DxLib_Init() == -1)
	{
		//エラーでリターン
		return -1;
	}

	if (!Initialize())//初期化に失敗した場合
	{
		DxLib_End();//dxlibを終了
		Effkseer_End();
		return -1;//エラーリターン
	}

	SetDrawScreen(DX_SCREEN_BACK);

	//while( 裏画面を表画面に反映,画面クリア )
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
	DxLib_End();//終了処理
	return 0;//終了
}

bool MyGame::EffekseerInit()
{
	// Effekseerを初期化する。
	// 引数には画面に表示する最大パーティクル数を設定する。
	if (Effkseer_Init(2000) == -1)
	{
		DxLib_End();
		return false;
	}
	// DXライブラリのデバイスロストした時のコールバックを設定する。
	// ウインドウとフルスクリーンの切り替えが発生する場合は必ず実行する。
	Effekseer_SetGraphicsDeviceLostCallbackFunctions();


	Effekseer_Set2DSetting(Screen::SCREEN_SIZE.x, Screen::SCREEN_SIZE.y);
	return true;
}

bool MyGame::Initialize()
{
	//エフェクトの初期化に失敗した場合 return
	if (!EffekseerInit()) return false;

	Mouse::GetInstance().Initialize();
	Loader::GetInstance().Initialize();
	SetBackgroundColor(0, 0, 255);
	//ワールド生成
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
