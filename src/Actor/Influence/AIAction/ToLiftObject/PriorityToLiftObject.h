#pragma once

//運べる物に進んでいく
#include"../Base/GamePriorityAction.h"
#include"Base/GameUsing.h"
#include<functional>
class PriorityToLiftObject : public GamePriorityAction
{
public:
	PriorityToLiftObject(float priority, IWorld& world, InfluenceID id, LerpCursor* cursor, UnitPtrs& units);
	~PriorityToLiftObject();

	//初期化
	void Initialize() override;
	//更新
	void Update(float deltaTime) override;
	void End() override;
	void Draw() const override;
private:
	//優先度を+αで計算する関数
	float OnPriority() override;
	bool Find(const LiftObject& lift);
	//目的とする持つオブジェクトの条件式
	virtual bool OnFind(const LiftObject& lift) = 0;
private:
	//目的の資源
	LiftObjectPtr m_target;
};