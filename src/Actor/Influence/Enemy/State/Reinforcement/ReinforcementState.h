#pragma once

#include"Base/Manager/State/IState.h"
#include"Base/GameUsing.h"
#include"../../FactoryStatusAI/FactoryStatusAI.h"
class IWorld;
#include"Base/AI/Priority/Shaft/Shaft.h"
class LerpCursor;
//�H����m�ی��AI
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
private:
	IWorld& m_world;
	//�O���Ƃ���ȊO�ŏグ��X�e�[�^�X��ύX����̂�
	FactoryStatusAI m_frontStatusAI;
	FactoryStatusAI m_backStatusAI;

	Shaft m_shaft;

	//�J�[�\��
	LerpCursor* m_cursor;
};