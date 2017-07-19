#ifndef	  _TITLE_SCENE_H_
#define	  _TITLE_SCENE_H_

#include"../Base/IScene.h"
#include<DxLib.h>
#include"Sprite\Sprite.h"
#include"Sprite\Base\SpriteManager.h"
//タイトルシーン
class TutoRealScene :public IScene
{
public:
	//コンストラクタ
	TutoRealScene();
	//デストラクタ
	~TutoRealScene();

	//開始
	virtual void Start()override;

	//更新
	virtual void Update(float deltaTime)override;

	//描画
	virtual void Draw()const override;

	//終了しているか
	virtual bool IsEnd()const override;

	//次のシーンを返す
	virtual Scene Next()const override;

	//終了
	virtual void End() override;
private:

	std::shared_ptr<SpriteManager> m_spriteManager;

	bool m_isEnd;
};

#endif