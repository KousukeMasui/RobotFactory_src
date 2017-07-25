#include "LoadScene.h"
#include<DxLib.h>
#include"Effect\Manager\EffectManager.h"
#include"Loader/Loader.h"
#include"UI/Sprite/Sprite.h"
#include"Screen\Screen.h"
#include"UI/Sprite/Action/Animation/Animation.h"
#include"MyGame\Base\FPS.h"
#include"Scene/Base/Scene.h"
#include"UI/Font/Action/AddText/AddTextAction.h"
#include"UI/Font/FontSprite.h"
LoadScene::LoadScene():
	IScene()
{
}

LoadScene::~LoadScene()
{
}

void LoadScene::ResourceLoad()
{
	//モデル読み込み
	Loader::GetInstance().ModelLoad(MODEL_ID::FACTORY, "res/Model/Factory/factory.mv1");
	Loader::GetInstance().ModelLoad(MODEL_ID::SKYDOME, "res/Model/mmd_skydome/Dome_X501.pmx");
	Loader::GetInstance().ModelLoad(MODEL_ID::GROUND, "res/Model/Field/field_test.mv1");
	Loader::GetInstance().ModelLoad(MODEL_ID::CLAMP_FIELD, "res/Model/Field/field_clamp_.mv1");
	Loader::GetInstance().ModelLoad(MODEL_ID::CIRCLE, "res/Model/Circle/circle_new.mv1");//Circle_0.01.mv1");
	Loader::GetInstance().ModelLoad(MODEL_ID::BOX, "res/Model/Shapes/BaseShape_Box.mv1");
	Loader::GetInstance().ModelLoad(MODEL_ID::UNIT, "res/Model/Unit/N_YAN.mv1");
	Loader::GetInstance().ModelLoad(MODEL_ID::PARTS, "res/Model/Parts/bolt1.mv1");
	Loader::GetInstance().ModelLoad(MODEL_ID::ROOT, "res/Model/Effect/root.mv1");
	//テクスチャ読み込み
	Loader::GetInstance().TextureLoad(TEXTURE_ID::TITLE_LOGO, "res/Texture/Title/title_logo.png");
	Loader::GetInstance().TextureLoad(TEXTURE_ID::CLICK_TO_START, "res/Texture/Title/click_to_start.png");
	Loader::GetInstance().TextureLoad(TEXTURE_ID::BLACK, "res/Texture/Command/black.png");
	Loader::GetInstance().TextureLoad(TEXTURE_ID::BACK, "res/Texture/Command/Back.png");
	Loader::GetInstance().TextureLoad(TEXTURE_ID::FACTORY, "res/Texture/Command/Factory.png");
	Loader::GetInstance().TextureLoad(TEXTURE_ID::CLOSE, "res/Texture/Command/Close.png");
	Loader::GetInstance().TextureLoad(TEXTURE_ID::CREATE, "res/Texture/Command/CreateUI.png");
	Loader::GetInstance().TextureLoad(TEXTURE_ID::HEAL_POWER, "res/Texture/Command/HealPowerUI.png");
	Loader::GetInstance().TextureLoad(TEXTURE_ID::HEAL_RANGE, "res/Texture/Command/HealRangeUI.png");
	Loader::GetInstance().TextureLoad(TEXTURE_ID::UNIT, "res/Texture/Command/Unit.png");
	Loader::GetInstance().TextureLoad(TEXTURE_ID::ATTACK_UP, "res/Texture/Command/ATK_CommandUI.png");
	Loader::GetInstance().TextureLoad(TEXTURE_ID::HP_UP, "res/Texture/Command/HP_CommandUI.png");
	Loader::GetInstance().TextureLoad(TEXTURE_ID::SPEED_UP, "res/Texture/Command/SPD_CommandUI.png");
	Loader::GetInstance().TextureLoad(TEXTURE_ID::AUTO, "res/Texture/Command/Auto.png");
	Loader::GetInstance().TextureLoad(TEXTURE_ID::COMMAND_FRAME, "res/Texture/gauge_frame.png");
	Loader::GetInstance().TextureLoad(TEXTURE_ID::COMMAND_GAUGE, "res/Texture/gauge.png");
	Loader::GetInstance().TextureLoad(TEXTURE_ID::PARTS, "res/Texture/Command/parts.png");
	Loader::GetInstance().TextureLoad(TEXTURE_ID::NUMBER, "res/Texture/number.png");
	Loader::GetInstance().TextureLoad(TEXTURE_ID::STATUS_BACK, "res/Texture/UnitStatus_Back.png");
	Loader::GetInstance().TextureLoad(TEXTURE_ID::RETRY, "res/Texture/Result/ReTry.png");
	Loader::GetInstance().TextureLoad(TEXTURE_ID::TO_TITLE, "res/Texture/Result/To_Title.png");
	Loader::GetInstance().TextureLoad(TEXTURE_ID::HAVE_PARTS, "res/Texture/have_parts.png");
	Loader::GetInstance().TextureLoad(TEXTURE_ID::HAVE_UNIT, "res/Texture/have_unit.png");
	Loader::GetInstance().TextureLoad(TEXTURE_ID::FACTORY_DEAD, "res/Texture/GamePlay/factory_dead.png");
	Loader::GetInstance().TextureLoad(TEXTURE_ID::FACTORY_GET, "res/Texture/GamePlay/factory_get.png");
	Loader::GetInstance().TextureLoad(TEXTURE_ID::FACTORY_LOST, "res/Texture/GamePlay/factory_lost.png");
	Loader::GetInstance().TextureLoad(TEXTURE_ID::HP_FRAME, "res/Texture/GamePlay/hpFrame.png");
	Loader::GetInstance().TextureLoad(TEXTURE_ID::HP_GAUGE, "res/Texture/GamePlay/hpGauge.png");
	//フォント読み込み
	Loader::GetInstance().FontLoad(Font_ID::SNAP_ITC, "res/Font/SnapITC.dft");
	Loader::GetInstance().FontLoad(Font_ID::JAPANISE_FONT, "res/Font/TestFont.dft");
}

void LoadScene::Initialize()
{
	//フォント読み込み
	Loader::GetInstance().FontLoad(Font_ID::SNAP_ITC, "res/Font/SnapITC.dft");
	auto font = std::make_shared<FontSprite>(Font_ID::SNAP_ITC, MyVector2(Screen::SCREEN_SIZE.x - 360.0f, Screen::SCREEN_SIZE.y - 69.0f), "Loading", Color::White);
	font->SetAction(std::make_shared<AddTextAction>("Loading", "...", 60.0f, true));
	m_manager.AddText(0,font);
	
	m_manager.AddSprite((int)TEXTURE_ID::BLACK, std::make_shared<Sprite>(TEXTURE_ID::BLACK, MyVector2(), MyVector2((float)Screen::SCREEN_SIZE.x, (float)Screen::SCREEN_SIZE.y), MyVector2(0.5f, 0.5f)));

	SetUseASyncLoadFlag(true);//非同期開始
	ResourceLoad();
	SetUseASyncLoadFlag(false);//非同期終了
}
void LoadScene::Update(float deltaTime)
{
	m_manager.Update(deltaTime);
}

void LoadScene::Draw() const
{
	//clsDx();
	//printfDx("残りロード数 %d\n", GetASyncLoadNum());
	m_manager.Draw();
	// 作成したフォントで画面左上に『Ｈｅｌｌｏｗ！！』と白色の文字列を描画する
	//DrawStringToHandle(0, 0, "NOWLOADING", GetColor(255, 255, 255), Loader::GetInstance().FontHandle(Font_ID::SNAP_IC));
}

bool LoadScene::IsEnd() const
{
	return GetASyncLoadNum() == 0;//非同期読み込みが終わったら
}

void LoadScene::End()
{
	m_manager.Clear();//画像を開放
}

int LoadScene::Next() const
{
	return (int)Scene::Title;
}
