#include "FactoryStatus.h"

#include<DxLib.h>
#include"CSVReader/CSVData.h"
#include"World/World.h"
FactoryStatus::FactoryStatus(IWorld& world, RootFind& find, FactoryParam& param) :
	maxHP(world.GetGameManager().GetCSV().Get_F(CSV_DATA_ID::FACTORY_MAX_HP,1)),
	hp(maxHP),
	healInterval(world.GetGameManager().GetCSV().Get_I(CSV_DATA_ID::FACTORY_HEAL_INTERVAL_SECOND,1)),
	partsCount(world.GetGameManager().GetCSV().Get_I(CSV_DATA_ID::FACTORY_INIT_PARTS,1)),
	m_create(world,find,param)
{
	status[FactoryStatusID::HEAL_POWER] = world.GetGameManager().GetCSV().Get_I(CSV_DATA_ID::FACTORY_INIT_HEAL_POWER, 1);
	status[FactoryStatusID::HEAL_RANGE] = world.GetGameManager().GetCSV().Get_I(CSV_DATA_ID::FACTORY_INIT_HEAL_RANGE, 1);
	status[FactoryStatusID::UNIT_ATK] = world.GetGameManager().GetCSV().Get_I(CSV_DATA_ID::FACTORY_INIT_UNIT_ATK, 1);
	status[FactoryStatusID::UNIT_HP] = world.GetGameManager().GetCSV().Get_I(CSV_DATA_ID::FACTORY_INIT_UNIT_HP, 1);
	status[FactoryStatusID::UNIT_SPD] = world.GetGameManager().GetCSV().Get_I(CSV_DATA_ID::FACTORY_INIT_UNIT_SPD, 1);
	status[FactoryStatusID::CREATE] = world.GetGameManager().GetCSV().Get_I(CSV_DATA_ID::FACTORY_INIT_CREATE, 1);
}
//生成時のステータスにして返す

UnitStatus FactoryStatus::CreateStatus(GameManager* manager) const
{
	return UnitStatus(status.at(FactoryStatusID::UNIT_HP)
		,status.at(FactoryStatusID::UNIT_ATK), status.at(FactoryStatusID::UNIT_SPD), 10.0f, manager);
}

int FactoryStatus::CreatePartsCount() const
{
	return status.at(FactoryStatusID::UNIT_HP) + status.at(FactoryStatusID::UNIT_ATK) + status.at(FactoryStatusID::UNIT_SPD) + 7;
}

int FactoryStatus::Total() const
{
	return status.at(FactoryStatusID::CREATE)+ healInterval + status.at(FactoryStatusID::HEAL_POWER) + status.at(FactoryStatusID::HEAL_RANGE);
}

bool FactoryStatus::IsStatusUp(FactoryStatusID status)
{
	bool isSufficient = this->status[status] <= partsCount;
	if (!isSufficient) return false;//そもそも資源が足りない場合、falseを返す
	if (status == FactoryStatusID::CREATE)//生成の場合は、ステータスの上限が無いのでtrue
		return true;
	else
		return this->status[status] < 20;
}

void FactoryStatus::StatusUp(FactoryStatusID status, GameManager* manager)
{
	partsCount -= this->status[status];
	if (status != FactoryStatusID::CREATE)//ステータスを上げる
	{
		this->status[status]++;
		//生成数が変わる可能性があるので
		this->status[FactoryStatusID::CREATE] = CreatePartsCount();
	}
	else//生成を行う
	{
		Create(CreateStatus(manager));
	}
}

void FactoryStatus::Create(const UnitStatus & status)
{
	m_create.Create(status);
}
