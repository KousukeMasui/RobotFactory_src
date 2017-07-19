#pragma once
#include"Base/Manager/State/IState.h"
#include"Base/GameUsing.h"
class Player;
class IWorld;
//ユニットに命令するステート
class PlayerOrderState : public IState
{
public:
	PlayerOrderState(IWorld& world, Player* player, UnitPtr* unit);
	~PlayerOrderState();
	void Initialize() override;
	void Update(float deltaTime) override;
	void Draw() const override;
	void End() override;
	int Next() const override;
	bool IsEnd() const override;
private:
	//工場の中をクリックしていないかチェック&停止位置を再指定
	void OrderClickFactory();
private:
	Player* m_player;
	UnitPtr* m_unit;
	bool m_isEnd;
	FactoryPtrs m_factorys;
};