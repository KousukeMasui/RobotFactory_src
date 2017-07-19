#pragma once

#include"Base/AI/Priority/PriorityAction.h"
class IWorld;
enum class InfluenceID;
class LerpCursor;
#include"Base/GameUsing.h"
#include"Base/Manager/State/StateManager.h"
//����̃Q�[���p��PriorityAction�p���N���X
class GamePriorityAction : public PriorityAction
{
public:
	GamePriorityAction(float priority, IWorld& world,InfluenceID id, LerpCursor* cursor,UnitPtrs& units);
	~GamePriorityAction();
protected:
	IWorld& m_world;
	InfluenceID m_influenceID;
	//���ߗp�J�[�\���|�C���^
	LerpCursor* m_cursor;
	//���j�b�g�ϐ��Q��
	UnitPtrs& m_units;
	//���ۂɖ��߂��郆�j�b�g
	UnitPtr m_orderUnit;
	StateManager m_cursorManager;
	//�����ŗD��x��ݒ肷��ۂɂ��� - �����̐��l��Ԃ�
	const float m_distancePriority;
};