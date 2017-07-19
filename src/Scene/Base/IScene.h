#ifndef	_ISCENE_H_
#define	_ISCENE_H_

enum class Scene;
#include"Base/Manager/State/IState.h"
//シーンインターフェース
class IScene : public IState
{
public:
	//仮想デストラクタ
	virtual ~IScene(){}
	//ゲーム開始
	virtual void Initialize() = 0;
	//更新
	virtual void Update(float deltaTime) = 0;
	//描画
	virtual void Draw()const = 0;
	//終了しているか
	virtual bool IsEnd()const = 0;
	//次のシーンを返す
	virtual int Next()const = 0;
	//終了
	virtual void End() = 0;


	/*
	*/
};

#endif