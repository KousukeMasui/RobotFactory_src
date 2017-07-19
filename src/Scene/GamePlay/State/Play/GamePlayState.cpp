#include "GamePlayState.h"
#include"World/World.h"
#include"../GamePlayStateID.h"
#include"../../GamePlaySpriteID.h"
#include"UI/Sprite/Sprite.h"
#include"Screen/Screen.h"
GamePlayState::GamePlayState(std::shared_ptr<World>& world):
	IState(),
	m_world(world)
{
	//ステータス表示のSpriteの生成
	auto statusBack = std::make_shared<Sprite>(TEXTURE_ID::STATUS_BACK, MyVector2(0, Screen::SCREEN_SIZE.y - 150.0f), MyVector2(1, 1), MyVector2(0.5f, 0.5f));

	m_world->GetUIManager().AddSprite((int)GamePlaySpriteID::NON_DELETE, statusBack);
	//ゲージのフレームを追加
	for (int i = 0; i < 20; i++)
	{
		for (int j = 1; j <= 3; j++)
		{
			auto gaugeFrame = std::make_shared<Sprite>(TEXTURE_ID::COMMAND_FRAME, MyVector2(135.0f + 15.0f * i, Screen::SCREEN_SIZE.y - 50.0f * j), MyVector2(1.0f, 1.0f), MyVector2(0.5f, 0.5f));
			m_world->GetUIManager().AddSprite((int)GamePlaySpriteID::NON_DELETE, gaugeFrame);
		}
	}
}

GamePlayState::~GamePlayState()
{
}

void GamePlayState::Initialize()
{
	m_world->GetCamera()->Controll(true);
}

void GamePlayState::Update(float deltaTime)
{
	m_world->Update(deltaTime);
}

void GamePlayState::Draw() const
{
}

void GamePlayState::End()
{
}

int GamePlayState::Next() const
{
	return (int)GamePlayStateID::COMMAND;
}

bool GamePlayState::IsEnd() const
{
	return m_world.get()->IsCommand();
}
