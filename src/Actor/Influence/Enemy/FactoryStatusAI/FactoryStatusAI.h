#pragma once

#include<vector>
#include"Base/GameUsing.h"
#include"Actor\UnitFactory\UnitFactory.h"
#include"Actor/UnitFactory/FactoryStatusID.h"
//�H��̃X�e�[�^�X���グ��AI�@�D��x�����߂Ă�������ɋ������s��
class FactoryStatusAI
{
private:
public:
	FactoryStatusAI();
	~FactoryStatusAI();

	//�D��x��ݒ肷��
	void SetPriority(const std::vector<FactoryStatusID>& priority);
	
	void PowerUp(FactoryPtrs& factorys);
	void PowerUp(FactoryPtr& factory);
private:
	//�グ��X�e�[�^�X�z��
	std::vector<FactoryStatusID> m_priority;
};