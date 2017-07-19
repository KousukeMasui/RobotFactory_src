#pragma once
#include"Scene\Base\IScene.h"
#include"UI/UIManager/UIManager.h"
//ロードシーン 非同期読み込みを使ってロードを行う
class LoadScene : public IScene
{
public:
	//コンストラクタ
	LoadScene();
	//デストラクタ
	~LoadScene();
	void Initialize() override;//初期化
	void Update(float deltaTime) override;//ロード時の更新処理
	void Draw() const override;
	bool IsEnd() const override;
	void End() override;
	int Next()const override;
private:
	//リソース読み込み　DxLib依存の物のみ有効
	void ResourceLoad();
private:
	UIManager m_manager;
};