#pragma once


//ユニットのゲーム状態で変化するステータス
class UnitStatus
{
public:
	UnitStatus(int factoryMaxHP = 0, float hp = 0.0f, int attack = 0, int speed = 0,float range = 0.0f);

	//現在のHPのパーセントを1~0で返す
	float hpPercent() const;
	//実際の移動速度を返す
	float MoveSpeed() const;
	int factoryMaxHP;	//体力の上限 工場用変数　maxHPはこれを元に計算する
	int maxHP;	//体力の上限
	float hp;		//現在の体力
	int attack;	//攻撃力
	int speed;	//移動速度
	float range;
};

UnitStatus operator +(const UnitStatus& s1, const UnitStatus& s2);
UnitStatus operator +=(UnitStatus& s1, const UnitStatus& s2);
UnitStatus operator -(const UnitStatus& s1, const UnitStatus& s2);
UnitStatus operator -=(UnitStatus& s1, const UnitStatus& s2);
bool operator ==(const UnitStatus& s1, const UnitStatus& s2);
bool operator !=(const UnitStatus& s1, const UnitStatus& s2);