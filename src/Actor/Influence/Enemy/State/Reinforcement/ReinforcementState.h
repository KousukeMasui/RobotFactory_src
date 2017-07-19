#pragma once

#include"Base/Manager/State/IState.h"
#include"Base/GameUsing.h"
class FactoryStatusAI;
class IWorld;
#include"Base/AI/Priority/Shaft/Shaft.h"
class LerpCursor;
//�H����m�ی��AI �p�[�c����ƃ��j�b�g��������ɍs��
//��������U��AI���쐬����
class ReinforcementState : public IState
{
public:
	ReinforcementState(IWorld& world, const Shaft& shaft, LerpCursor* cursor, UnitPtrs& units);
	~ReinforcementState();

	virtual void Initialize()override;
	virtual void Update(float deltaTime)override;
	void Draw() const {}
	virtual void End()override;
	virtual int Next()const override;
	virtual bool IsEnd()const override;
private:
	//�����֐�
	void PowerUp();
	//��肪���Ȃ��H����U������AI
	bool WeakFactoryAttack(UnitPtrs& units,const FactoryPtrs& myFactorys);
private:
	IWorld& m_world;
	//�O���Ƃ���ȊO�ŏグ��X�e�[�^�X��ύX����̂�
	std::shared_ptr<FactoryStatusAI> m_frontStatusAI;
	std::shared_ptr<FactoryStatusAI> m_backStatusAI;

	Shaft m_shaft;

	//�J�[�\��
	LerpCursor* m_cursor;
};