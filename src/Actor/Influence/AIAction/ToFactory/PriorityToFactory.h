#pragma once
#include"../Base/GamePriorityAction.h"
#include"Math/Vector/MyVector3.h"
class PriorityToFactory : public GamePriorityAction
{
public:
	PriorityToFactory(float priority, IWorld& world, InfluenceID id, LerpCursor* cursor, UnitPtrs& units,bool isContainsCheck = true);
	PriorityToFactory(float priority, IWorld& world, InfluenceID id, LerpCursor* cursor, UnitPtrs& units,UnitFactory& target);

	//������
	virtual void Initialize() override;
	//�X�V
	void Update(float deltaTime) override;
	void End() override;
	void Draw() const override;

protected:
	float OnPriority() override;
	virtual bool IsDisablePriority(const UnitPtr& unit)const {
		return false;
	}
	virtual UnitPtrs GetUnits() ;
	//���j�b�g�ɑ΂��Ĉ�ԋ߂��H��܂ł̋��������߂�
	float NearFactoryDistance(const UnitPtr& unit, UnitFactory* factory);
	//���j�b�g�ɑ΂��Ĉ�ԋ߂��H��܂ł̋��������߂�
	float NearFactoryDistance(const UnitPtr& unit);
protected:
	UnitFactory* m_targetFactory;

	MyVector3 m_targetPos;

	//�H���T����
	bool m_isFactorySearch;

	//���ɑ_���Ă���ꍇ���̍H������O���邩
	bool m_isContainsCheck;
};