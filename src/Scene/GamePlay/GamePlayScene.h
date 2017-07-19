#ifndef	  _GAMEPLAY_SCENE_H_
#define	  _GAMEPLAY_SCENE_H_

#include"../Base/IScene.h"
#include"Model/StaticModel/StaticModel.h"
#include<memory>
#include"Base/Manager/State/StateManager.h"
class World;
//ゲームプレイシーン
class GamePlayScene :public IScene
{
public:
	//コンストラクタ
	explicit GamePlayScene(const std::shared_ptr<World>& world,bool& isWin);
	//デストラクタ
	~GamePlayScene();

	virtual void Initialize() override;
	virtual void Update(float deltaTime) override;
	void EndUpdate(float deltaTime);
	virtual void Draw()const override;
	void EndDraw() const;

	//終了しているか
	virtual bool IsEnd()const override;

	//次のシーンを返す
	virtual int Next()const override;

	virtual void End() override;

private:
	std::shared_ptr<World> m_world;

	StateManager m_stateManager;
	bool m_isEnd;

	bool m_isEndEffect;//終了時の演出開始時にtrue

	bool& m_isWin;//勝利時true
};


#endif