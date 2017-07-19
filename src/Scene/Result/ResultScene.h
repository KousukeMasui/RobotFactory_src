#pragma once


#include"../Base/IScene.h"
#include<DxLib.h>
class World;
#include<memory>
#include"UI/UIManager/UIManager.h"
//タイトルシーン
class ResultScene :public IScene
{
public:
	//コンストラクタ
	explicit ResultScene(const std::shared_ptr<World>& world,bool& isWin);
	//デストラクタ
	~ResultScene();
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
	bool& m_isWin;
	bool m_isEnd;
	Scene m_nextScene;
};