#include"GamePlayScene.h"
#include"../Base/Scene.h"
#include"../../Actor/Base/IWorld.h"
#include"../../Actor/Base/ActorGroup.h"

#include"Input/Mouse/Mouse.h"
#include"Loader/Loader.h"
#include"Actor/Unit/Unit.h"


#include"Base/RoadFinder/PathFinder.h"

#include"Effect\Manager\EffectManager.h"
#include"World\World.h"
#include"GamePlaySpriteID.h"
#include"State/Play/GamePlayState.h"
#include"State/Command/GamePlayCommand.h"
#include"State/Auto/GamePlayAutoState.h"
#include"State/GamePlayStateID.h"
#include"Input/InputManager.h"
//コンストラクタ
GamePlayScene::GamePlayScene(const std::shared_ptr<World>& world, bool& isWin) :
m_world(world),
m_isEnd(false),
m_isEndEffect(false),
m_isWin(isWin)
{
	Loader::GetInstance().EffectLoad(EffectID::HEAL, "./res/Effect/Heal_.efk");
	Loader::GetInstance().EffectLoad(EffectID::POWER_UP, "./res/Effect/PowerUp.efk");


}
//デストラクタ
GamePlayScene::~GamePlayScene()
{
}

void GamePlayScene::Initialize()
{
	m_isEnd = false;
	m_world->GameStart();
	m_world->AddCamera(CameraMode::NORMAL, std::make_shared<Camera>());
	m_stateManager.Initialize();
	m_stateManager.Add((int)GamePlayStateID::PLAY, std::make_shared<GamePlayState>(m_world));
	m_stateManager.Add((int)GamePlayStateID::COMMAND, std::make_shared<GamePlayCommand>(*m_world));
	m_stateManager.Add((int)GamePlayStateID::AUTO_SELECT, std::make_shared<GamePlayAutoState>(*m_world));
	m_stateManager.SetState((int)GamePlayStateID::PLAY);
	
}
void GamePlayScene::Update(float deltaTime)
{
	if (m_isEndEffect)
	{
		EndUpdate(deltaTime);
	}
	else
	{
		InputManager::GetInstance().Update();
	}

	m_stateManager.Update(deltaTime);

	//エネミーの工場が無い場合
	if (m_world->GetGameManager().GetFactoryManager().GetVector(InfluenceID::ENEMY).empty())
	{
		//勝利
		m_isEnd = true;
		m_isWin = true;
	}
	else if (m_world->GetGameManager().GetFactoryManager().GetVector(InfluenceID::PLAYER).empty())
	{
		//敗北
		m_isEnd = true;
		m_isWin = false;
	}
}

void GamePlayScene::EndUpdate(float deltaTime)
{
	/*ここにクリア時のUpdate処理を*/

	m_isEnd = true;
}

void GamePlayScene::Draw()const
{
	if (m_isEndEffect)
		EndDraw();
	SetUseLighting(true);
	m_world->Draw();
	m_stateManager.Draw();
}

void GamePlayScene::EndDraw() const
{
}

//終了しているか
bool GamePlayScene::IsEnd()const
{
	return m_isEnd;
}

//次のシーンを返す
int GamePlayScene::Next()const
{
	return (int)Scene::Result;
}

void GamePlayScene::End()
{
}