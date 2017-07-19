#pragma once

#include<vector>
#include"Base/GameUsing.h"
#include"Actor\UnitFactory\UnitFactory.h"
#include"Actor/UnitFactory/FactoryStatusID.h"
//工場のステータスを上げるAI　優先度を決めてそれを元に強化を行う
class FactoryStatusAI
{
private:
public:
	FactoryStatusAI();
	~FactoryStatusAI();

	//優先度を設定する
	void SetPriority(const std::vector<FactoryStatusID>& priority);
	
	void PowerUp(FactoryPtrs& factorys);
	void PowerUp(FactoryPtr& factory);
private:
	//上げるステータス配列
	std::vector<FactoryStatusID> m_priority;
};