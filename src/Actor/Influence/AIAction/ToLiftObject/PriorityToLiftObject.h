#pragma once

//�^�ׂ镨�ɐi��ł���
#include"../Base/GamePriorityAction.h"
#include"Base/GameUsing.h"
#include<functional>
class PriorityToLiftObject : public GamePriorityAction
{
public:
	PriorityToLiftObject(float priority, IWorld& world, InfluenceID id, LerpCursor* cursor, UnitPtrs& units);
	~PriorityToLiftObject();

	//������
	void Initialize() override;
	//�X�V
	void Update(float deltaTime) override;
	void End() override;
	void Draw() const override;
private:
	//�D��x��+���Ōv�Z����֐�
	float OnPriority() override;
	bool Find(const LiftObject& lift);
	//�ړI�Ƃ��鎝�I�u�W�F�N�g�̏�����
	virtual bool OnFind(const LiftObject& lift) = 0;
private:
	//�ړI�̎���
	LiftObjectPtr m_target;
};