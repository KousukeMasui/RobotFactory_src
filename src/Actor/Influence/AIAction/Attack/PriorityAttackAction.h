#pragma once
#include"../Base/GamePriorityAction.h"
#include"Base/AI/Priority/Shaft/Shaft.h"
//ちょっと長め　一つの工場を落とすために行動する
class PriorityAttackAction : public GamePriorityAction
{
public:
	PriorityAttackAction(float priority, IWorld& world, InfluenceID id, LerpCursor* cursor, UnitPtrs& units);

	//初期化
	virtual void Initialize() override;
	//更新
	void Update(float deltaTime) override;
	void End() override;
	void Draw() const override;

protected:
	float OnPriority() override;
private:
	//一番弱い工場を取得
	FactoryPtr GetWeakFactory(float& power);

private:
	Shaft m_shaft;
	UnitPtrs m_orderUnits;
	UnitPtrs m_targets;
	FactoryPtr m_targetFactory;
};