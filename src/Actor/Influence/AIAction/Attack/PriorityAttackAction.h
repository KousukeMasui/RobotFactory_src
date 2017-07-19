#pragma once
#include"../Base/GamePriorityAction.h"
#include"Base/AI/Priority/Shaft/Shaft.h"
//������ƒ��߁@��̍H��𗎂Ƃ����߂ɍs������
class PriorityAttackAction : public GamePriorityAction
{
public:
	PriorityAttackAction(float priority, IWorld& world, InfluenceID id, LerpCursor* cursor, UnitPtrs& units);

	//������
	virtual void Initialize() override;
	//�X�V
	void Update(float deltaTime) override;
	void End() override;
	void Draw() const override;

protected:
	float OnPriority() override;
private:
	//��Ԏア�H����擾
	FactoryPtr GetWeakFactory(float& power);

private:
	Shaft m_shaft;
	UnitPtrs m_orderUnits;
	UnitPtrs m_targets;
	FactoryPtr m_targetFactory;
};