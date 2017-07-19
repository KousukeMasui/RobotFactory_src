#include"TitleScene.h"

#include"../Base/Scene.h"
#include"Input/Input.h"
#include"UI/UIAction/Link/Link.h"
#include"UI/UIAction/SameTime/SameTime.h"
#include"Loader\Loader.h"
#include"Input/Mouse/Mouse.h"
#include"UI/UIAction/Link/Link.h"
#include"UI/UIAction/Move/Move.h"
#include"UI/UIAction/Fade/Fade.h"
#include"UI/Sprite/Action/MouseClickFunc/MouseClickFunc.h"
#include"World\World.h"
#include"Actor\Camera/TitleCamera\TitleCamera.h"
TitleScene::TitleScene(const std::shared_ptr<World>& world) :
	m_world(world),
	m_isEnd(false)
{
}
//デストラクタ
TitleScene::~TitleScene()
{
}

//開始
void TitleScene::Initialize()
{
	m_isEnd = false;

	m_UIManager = std::make_shared<UIManager>();
	//タイトルロゴの設定
	
		auto logo = std::make_shared<Sprite>(TEXTURE_ID::TITLE_LOGO, MyVector2(193, -500), MyVector2(1,1), MyVector2(0.5f, 0.5f));

		//アクションの設定
		//上から降ってくる
		auto move = std::make_shared<Move>(MyVector2(193, -500), MyVector2(193, 11), 60.0f);

		logo->SetAction(move);
		m_UIManager->AddSprite((int)TEXTURE_ID::TITLE_LOGO, logo);
	
	//クリック画像の設定
	{
		auto click = std::make_shared<Sprite>(TEXTURE_ID::CLICK_TO_START, MyVector2(242, 520), MyVector2(2.3f, 2.3f), MyVector2(0.5f, 0.5f));

		std::shared_ptr<UIAction> action = std::make_shared<Link>(2, true, std::make_shared<Fade>(1.0f, 0.0f, 60.0f), std::make_shared<Fade>(0.0f, 1.0f, 60.0f));
		click->SetAction(action);
		//logo->Add(click);
		m_UIManager->AddSprite((int)TEXTURE_ID::CLICK_TO_START, click);
	}

	m_world->StageCreate();
	m_world->AddCamera(CameraMode::NORMAL, std::make_shared<TitleCamera>());
}

//更新
void TitleScene::Update(float deltaTime)
{
	m_UIManager->Update(deltaTime);

	if (Mouse::GetInstance().IsPressUp(MouseCommand::LEFT))
	{
		m_isEnd = true;
	}
	m_world->Update(deltaTime);
}

//描画
void TitleScene::Draw()const
{
	m_world->Draw();
	m_UIManager->Draw();
	//FontText::Draw(Font::SNAP_ITC, "HP", Point2(0, 0), Color(1, 0, 0, 1));
}

//終了しているか
bool TitleScene::IsEnd()const
{
	return m_isEnd;
}

//次のシーンを返す
int TitleScene::Next()const
{
	return (int)Scene::GamePlay;
}

//終了
void TitleScene::End()
{
	m_UIManager = nullptr;
}