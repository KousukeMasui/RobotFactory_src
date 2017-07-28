#pragma once
class IWorld;
#include"Base/Manager/State/StateManager.h"
#include<vector>
#include"Math/Point2/Point2.h"

#include<map>
#include"Base/GameUsing.h"

#include"Cursor/LerpCursor.h"
#include"../Base/Influence.h"
class Enemy : public Influence
{
public:
	explicit Enemy(IWorld& world);
	~Enemy();

	void Update(float deltaTime) override;
	void Draw() const override;

	LerpCursor& Cursor();

private:
	//���߂��郆�j�b�g��ݒ肷��
	void OrderUnitSet();

private:
	//AI�̃X�e�[�g�p�^�[���̓����N���X
	StateManager m_stateManager;

	//�J�[�\���N���X
	LerpCursor m_cursor;
	UnitPtrs m_units;
};