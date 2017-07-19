#ifndef	  _TITLE_SCENE_H_
#define	  _TITLE_SCENE_H_

#include"../Base/IScene.h"
#include<DxLib.h>
#include"UI/UIManager/UIManager.h"
#include<memory>
class World;
//タイトルシーン
class TitleScene :public IScene
{
public:
	//コンストラクタ
	explicit TitleScene(const std::shared_ptr<World>& world);
	//デストラクタ
	~TitleScene();
	//開始
	virtual void Initialize()override;

	//更新
	virtual void Update(float deltaTime)override;

	//描画
	virtual void Draw()const override;

	//終了しているか
	virtual bool IsEnd()const override;

	//次のシーンを返す
	virtual int Next()const override;

	//終了
	virtual void End() override;
private:
	std::shared_ptr<World> m_world;
	std::shared_ptr<UIManager> m_UIManager;

	bool m_isEnd;
};

#endif