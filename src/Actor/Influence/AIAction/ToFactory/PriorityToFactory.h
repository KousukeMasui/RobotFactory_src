#pragma once
#include"../Base/GamePriorityAction.h"
#include"Math/Vector/MyVector3.h"
class PriorityToFactory : public GamePriorityAction
{
public:
	PriorityToFactory(float priority, IWorld& world, InfluenceID id, LerpCursor* cursor, UnitPtrs& units,bool isContainsCheck = true);
	PriorityToFactory(float priority, IWorld& world, InfluenceID id, LerpCursor* cursor, UnitPtrs& units,UnitFactory& target);

	//初期化
	virtual void Initialize() override;
	//更新
	void Update(float deltaTime) override;
	void End() override;
	void Draw() const override;

protected:
	float OnPriority() override;
	virtual bool IsDisablePriority(const UnitPtr& unit)const {
		return false;
	}
	virtual UnitPtrs GetUnits() ;
	//ユニットに対して一番近い工場までの距離を求める
	float NearFactoryDistance(const UnitPtr& unit, UnitFactory* factory);
	//ユニットに対して一番近い工場までの距離を求める
	float NearFactoryDistance(const UnitPtr& unit);
protected:
	UnitFactory* m_targetFactory;

	MyVector3 m_targetPos;

	//工場を探すか
	bool m_isFactorySearch;

	//既に狙っている場合その工場を除外するか
	bool m_isContainsCheck;
};