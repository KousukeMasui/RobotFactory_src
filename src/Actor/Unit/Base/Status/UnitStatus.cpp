#include "UnitStatus.h"
#include<cmath>
#include<float.h>
#include"Manager/GameManager.h"
UnitStatus::UnitStatus(int hpLevel, int attackLevel, int speedLevel, float range, GameManager* manager)
{
	m_levels[UNIT_STATUS_ID::HP] = hpLevel;
	m_levels[UNIT_STATUS_ID::ATK] = attackLevel;
	m_levels[UNIT_STATUS_ID::SPD] = speedLevel;

	m_status[UNIT_STATUS_ID::HP] = manager->GetCSV().Get_F(CSV_DATA_ID::UNIT_HP, hpLevel);
	m_status[UNIT_STATUS_ID::MAX_HP] = m_status[UNIT_STATUS_ID::HP];

	m_status[UNIT_STATUS_ID::ATK] = manager->GetCSV().Get_F(CSV_DATA_ID::UNIT_ATK, attackLevel);
	m_status[UNIT_STATUS_ID::SPD] = manager->GetCSV().Get_F(CSV_DATA_ID::UNIT_SPD, speedLevel);
	m_status[UNIT_STATUS_ID::RANGE] = range;
}

//現在のHPのパーセントを1~0で返す
float UnitStatus::hpPercent() const
{
	return (m_status.at(UNIT_STATUS_ID::HP) / m_status.at(UNIT_STATUS_ID::MAX_HP));
}

int UnitStatus::Level(UNIT_STATUS_ID id) const
{
	return m_levels.at(id);
}

float UnitStatus::Status(UNIT_STATUS_ID id) const
{
	return m_status.at(id);
}

void UnitStatus::AddHP(float hp)
{
	m_status[UNIT_STATUS_ID::HP] = std::fminf(m_status[UNIT_STATUS_ID::HP] + hp,
		m_status[UNIT_STATUS_ID::MAX_HP]);
}

UnitStatus operator+(const UnitStatus & s1, const UnitStatus & s2)
{
	int hp = s1.Level(UNIT_STATUS_ID::HP) + s2.Level(UNIT_STATUS_ID::HP);
	int atk = s1.Level(UNIT_STATUS_ID::ATK) + s2.Level(UNIT_STATUS_ID::ATK);
	int spd = s1.Level(UNIT_STATUS_ID::SPD) + s2.Level(UNIT_STATUS_ID::SPD);
	float range = s1.Status(UNIT_STATUS_ID::RANGE) + s2.Status(UNIT_STATUS_ID::RANGE);
	return UnitStatus(hp,atk,spd, range);
}

UnitStatus operator+=(UnitStatus & s1, const UnitStatus & s2)
{
	s1 = s1 + s2;
	return s1;
}

UnitStatus operator -(const UnitStatus& s1, const UnitStatus& s2)
{
	int hp = s1.Level(UNIT_STATUS_ID::HP) - s2.Level(UNIT_STATUS_ID::HP);
	int atk = s1.Level(UNIT_STATUS_ID::ATK) - s2.Level(UNIT_STATUS_ID::ATK);
	int spd = s1.Level(UNIT_STATUS_ID::SPD) - s2.Level(UNIT_STATUS_ID::SPD);
	float range = s1.Status(UNIT_STATUS_ID::RANGE) - s2.Status(UNIT_STATUS_ID::RANGE);
	return UnitStatus(hp, atk, spd, range);
}
UnitStatus operator -=(UnitStatus& s1, const UnitStatus& s2)
{
	s1 = s1 - s2;
	return s1;
}