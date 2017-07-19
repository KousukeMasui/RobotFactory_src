#ifndef	 _SCENE_MANAGER_H_
#define	 _SCENE_MANAGER_H_

enum class Scene;
#include"IScenePtr.h"
#include<unordered_map>
#include"UI/Sprite/Base/SpritePtr.h"
#include"Base/Manager/State/StateManager.h"
//シーンマネージャー
class SceneManager
{
public:
	//コンストラクタ
	SceneManager();
	//初期化
	void Initialize();
	//更新
	void Update(float deltaTime);

	//描画
	void Draw();

	//シーンの追加
	void Add(Scene name, const IScenePtr& scene);
	//シーンの変更
	void Change(Scene scene);

	//コピー禁止
	SceneManager(const SceneManager& other) = delete;
	SceneManager operator=(const SceneManager& other) = delete;
private:
	//シーンを入れるステートマネージャー
	StateManager m_manager;
	SpritePtr m_fadeSprite;
};

#endif