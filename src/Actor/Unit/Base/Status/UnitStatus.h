#pragma once

#include<map>
	enum class UNIT_STATUS_ID {
		HP = 0,
		ATK,
		SPD,
		RANGE,
		MAX_HP
	};
class GameManager;
//ユニットのゲーム状態で変化するステータス
class UnitStatus
{
public:
	UnitStatus(int hpLevel = 0, int attackLevel = 0, int speedLevel = 0, float range = 0.0f, GameManager* manager = nullptr);

	//現在のHPのパーセントを1~0で返す
	float hpPercent() const;

	int Level(UNIT_STATUS_ID id) const;
	float Status(UNIT_STATUS_ID id) const;

	void AddHP(float hp);
private:
	//工場のステータスを受け取る
	std::map<UNIT_STATUS_ID, int> m_levels;
	//ゲーム上の実際のステータス
	std::map<UNIT_STATUS_ID, float> m_status;
};

UnitStatus operator +(const UnitStatus& s1, const UnitStatus& s2);
UnitStatus operator +=(UnitStatus& s1, const UnitStatus& s2);
UnitStatus operator -(const UnitStatus& s1, const UnitStatus& s2);
UnitStatus operator -=(UnitStatus& s1, const UnitStatus& s2);