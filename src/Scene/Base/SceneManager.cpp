#include"SceneManager.h"

#include"SceneNull.h"
#include"UI/Sprite/Sprite.h"
#include"UI/UIAction/Fade/Fade.h"
#include"UI/UIAction/Link/Link.h"
#include"Loader/Loader.h"
#include"Screen/Screen.h"
//コンストラクタ
SceneManager::SceneManager()
{

}
//初期化
void SceneManager::Initialize()
{
	Loader::GetInstance().TextureLoad(TEXTURE_ID::BLACK, "res/Texture/Command/black.png");
	m_fadeSprite = std::make_shared<Sprite>(TEXTURE_ID::BLACK, MyVector2(), MyVector2((float)Screen::SCREEN_SIZE.x, (float)Screen::SCREEN_SIZE.y), MyVector2(0.5f, 0.5f));
	m_fadeSprite->Alpha(0.0f);

	m_manager.SetFunc(
		[&]() {m_fadeSprite->SetAction(std::make_shared<Fade>(0.0f, 1.0f, 60.0f)); },
		[&]() {m_fadeSprite->SetAction(std::make_shared<Fade>(1.0f, 0.0f, 60.0f)); },
		[&](float deltaTime) { return m_fadeSprite->Update(deltaTime); });
}
//更新
void SceneManager::Update(float deltaTime)
{
	m_manager.Update(deltaTime);
}

//描画
void SceneManager::Draw()
{
	m_manager.Draw();
	m_fadeSprite->Draw();
}

//シーンの追加
void SceneManager::Add(Scene id, const IScenePtr& scene)
{
	m_manager.Add((int)id, scene);
}
void SceneManager::Change(Scene scene)
{
	m_manager.SetState((int)scene);
}