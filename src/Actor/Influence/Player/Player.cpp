#include "Player.h"
#include"Input\Mouse\Mouse.h"
#include"Screen\Screen.h"
#include<DxLib.h>
#include"Actor/Base/IWorld.h"
#include"World/World.h"
#include"Base/RoadFinder/Map/FieldMap.h"
#include"Base/RoadFinder/PathFind3DUtility.h"
#include"Actor\UnitFactory\UnitFactory.h"
#include"UI/Sprite/Sprite.h"
#include"Math/Collision/Model/ModelCollision.h"
#include"Base/VectorUtility/VectorUtility.h"
#include"Actor/Unit/AITree/Node/UnitNodeID.h"
#include"State/Select/PlayerSelectState.h"
#include"State/Order/PlayerOrderState.h"
#include"State/PlayerStateID.h"
#include"Scene/GamePlay/GamePlaySpriteID.h"

const MyVector3 DEFAULT_CURSOR_SCALE = MyVector3(20, 1, 20);		//初期のカーソルサイズ
const MyVector3 COL_FACTORY_CURSOR_SCALE = MyVector3(80, 1, 80);	//工場を選択している際のカーソルサイズ
Player::Player(IWorld & world):
	Influence(world,InfluenceID::PLAYER),
	m_model(MODEL_ID::CIRCLE),
	m_isAutoSelect(false),
	m_mouseSelect(world)
{
	m_stateManager.Add((int)PlayerStateID::SELECT, std::make_shared<PlayerSelectState>(world,this));
	m_stateManager.Add((int)PlayerStateID::ORDER, std::make_shared<PlayerOrderState>(world,this,&m_selectedUnit));
	m_stateManager.SetState((int)PlayerStateID::SELECT);
}

Player::~Player()
{
}

void Player::Update(float deltaTime)
{
	//マウスの先のユニットを取得
	m_onMouseUnit = m_mouseSelect.Update(deltaTime);

	m_stateManager.Update(deltaTime);

	CursorEffect();
	//マウスの位置のユニットのステータス描画のSpriteを追加
	OnMouseUnitStatusDraw();
}

void Player::Draw() const
{
	SelectUnitDraw();//選択ユニットにカーソル描画
	m_mouseSelect.Draw();//カーソル描画
}
void Player::Select(const UnitPtr & unit)
{
	m_selectedUnit = m_onMouseUnit;
	//命令待ちにする
	m_selectedUnit->RoadDelete();
}
SelectCursor & Player::GetCursor()
{
	return m_mouseSelect.GetCursor();
}

void Player::OnMouseUnitStatusDraw()
{
	//ゲージ画像を消す
	m_world.GetUIManager().DeleteSprite((int)GamePlaySpriteID::PLAY_GAUGE);
	//マウスがユニットの位置にない場合
	if (m_onMouseUnit == nullptr)
	{
		return;//早期リターン
	}

	//繰り返すが、関数にするまでもないのでラムダを作る
	auto gaugeDraw = [&](int num, MyVector2 startPosition)
	{
		for (int i = 0; i < num; i++)
		{
			auto gaugeSprite = std::make_shared<Sprite>(TEXTURE_ID::COMMAND_GAUGE, startPosition + 15.0f * i, MyVector2(1.0f, 1.0f), MyVector2(0.5f, 0.5f));
			m_world.GetUIManager().AddSprite((int)GamePlaySpriteID::PLAY_GAUGE, gaugeSprite);
		}
	};

	//HPの描画
	gaugeDraw(m_onMouseUnit->GetStatus().factoryMaxHP, MyVector2(135,Screen::SCREEN_SIZE.y - 150.0f));
	//攻撃力の描画
	gaugeDraw(m_onMouseUnit->GetStatus().attack, MyVector2(135, Screen::SCREEN_SIZE.y - 100.0f));
	//速度の描画
	gaugeDraw(m_onMouseUnit->GetStatus().speed, MyVector2(135, Screen::SCREEN_SIZE.y - 50.0f));
}

void Player::SelectUnitDraw() const
{
	if (m_selectedUnit == nullptr) return;
	auto position = m_selectedUnit->Position() + MyVector3(0, 2, 0);
	//範囲のモデルの色を変える
	m_model.SetMaterialColor(0, Color(0.0f, 0.0f, 1.0f, 1.0f));

	m_model.Draw(position, MyVector3(13, 1, 13), 0.0f);
}

void Player::CursorEffect()
{
	//カーソルの大きさを初期サイズにする
	m_mouseSelect.GetCursor().Scale(DEFAULT_CURSOR_SCALE);
	if (m_onMouseUnit != nullptr)
	{
		m_mouseSelect.GetCursor().Position(m_onMouseUnit->Position());
		return;
	}

	auto factorys = m_world.GetGameManager().GetFactoryManager().All();
	for (auto factory : factorys)
	{
		if (factory->GetParam().m_box.IsCollide(Sphere(m_mouseSelect.GetCursor().Position(), 1.0f)).isHit)
		{
			m_mouseSelect.GetCursor().Position(factory->GetParam().Position());
			m_mouseSelect.GetCursor().Scale(COL_FACTORY_CURSOR_SCALE);
			break;
		}
	}
}
