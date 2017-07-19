#ifndef	_SCENE_NULL_H_
#define	_SCENE_NULL_H_

#include"IScene.h"

//空のシーン
class SceneNull :public IScene
{
public:
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
};

#endif