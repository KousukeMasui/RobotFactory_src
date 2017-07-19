#pragma once


#include"Base/Manager/State/IState.h"
#include"UI/UIManager/UIManager.h"
#include"Actor/Influence/MouseSelect/MouseSelect.h"
#include"UI/Sprite/Base/WorldToSpriteManager.h"
class IWorld;
//工場の自動回収ユニット選択ステート
class GamePlayAutoState : public IState
{
public:
	explicit GamePlayAutoState(IWorld& world);
	~GamePlayAutoState();

	void Initialize() override;
	void Update(float deltaTime) override;
	void Draw() const override;
	void End() override;
	int Next() const override;
	bool IsEnd() const override;
private:
	IWorld& m_world;
	UIManager m_manager;
	MouseSelect m_mouseSelect;
	WorldToSpriteManager m_worldSpriteManager;
};