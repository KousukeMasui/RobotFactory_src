#include "GamePlayAutoState.h"
#include"UI/Sprite/Sprite.h"
#include"Input/Mouse/Mouse.h"
#include"../GamePlayStateID.h"
#include"World/World.h"
#include"Actor/UnitFactory/UnitFactory.h"
#include"UI/Font/FontSprite.h"
#include"UI/UIAction/Move/Move.h"
#include"UI/UIAction/Link/Link.h"
#include"Screen/Screen.h"
GamePlayAutoState::GamePlayAutoState(IWorld& world):
	m_world(world),
	m_mouseSelect(world)
{
	m_manager.AddSprite(0, std::make_shared<Sprite>(TEXTURE_ID::BACK, MyVector2(30, 30), MyVector2(1, 1), MyVector2(0, 0)));
	//文字描画
	auto fontSprite = std::make_shared<FontSprite>(Font_ID::JAPANISE_FONT, 
		MyVector2((float)Screen::SCREEN_SIZE.x, ((float)Screen::SCREEN_SIZE.y - 210)), "ユニットを選択して下さい", Color::Black);
	fontSprite->SetAction(std::make_shared<Link>(1, true, std::make_shared<Move>(MyVector2((float)Screen::SCREEN_SIZE.x, ((float)Screen::SCREEN_SIZE.y - 210)), MyVector2(-800.0f, ((float)Screen::SCREEN_SIZE.y - 210)), 600.0f)));
	m_manager.AddText(1, fontSprite);
	m_worldSpriteManager.Set(TEXTURE_ID::AUTO);
}

GamePlayAutoState::~GamePlayAutoState()
{
}

void GamePlayAutoState::Initialize()
{
	//カメラ操作を有効に
	m_world.GetCamera()->Controll(true);
}

void GamePlayAutoState::Update(float deltaTime)
{
	//カメラの更新処理
	m_world.GetCamera()->Update(deltaTime);
	//マウスカーソルがユニットに触れていたら取得
	auto unit = m_mouseSelect.Update(deltaTime);
	//左クリックされたら
	if (Mouse::GetInstance().IsPressUp(MouseCommand::LEFT))
	{
		//ユニットを工場に
		m_world.GetCommandFactory()->SelectUnit(unit);
	}
	//UIデータを更新
	m_worldSpriteManager.Clear();
	auto units = m_world.GetCommandFactory()->GetAutoUnits();
	for (auto u : units)
	{
		m_worldSpriteManager.Save(TEXTURE_ID::AUTO, u->Position() + MyVector3(0, 40, 0), MyVector2(20, 20));
	}
	m_manager.Update(deltaTime);
}

void GamePlayAutoState::Draw() const
{
	m_manager.Draw();
	m_mouseSelect.Draw();
	m_worldSpriteManager.Draw();
}

void GamePlayAutoState::End()
{
	m_worldSpriteManager.Clear();
}

int GamePlayAutoState::Next() const
{
	return (int)GamePlayStateID::COMMAND;
}

bool GamePlayAutoState::IsEnd() const
{
	return Mouse::GetInstance().IsPressUp(MouseCommand::LEFT) && 
		m_manager.FindSprite(0)->IsCollide(Mouse::GetInstance().Position());
}
