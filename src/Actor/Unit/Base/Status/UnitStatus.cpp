#include "UnitStatus.h"
#include<cmath>
#include<float.h>
UnitStatus::UnitStatus(int factoryMaxHP, float hp, int attack, int speed, float range) :
	factoryMaxHP(factoryMaxHP),
	maxHP(factoryMaxHP * 10),
	hp(hp),
	attack(attack),
	speed(speed),
	range(range)
{

}

//現在のHPのパーセントを1~0で返す
float UnitStatus::hpPercent() const
{
	return (hp / maxHP);
}

float UnitStatus::MoveSpeed() const
{
	return 1.0f + speed * 0.2f;
}

UnitStatus operator+(const UnitStatus & s1, const UnitStatus & s2)
{
	float hp = s1.hp + s2.hp;
	int atk = s1.attack + s2.attack;
	int spd = s1.speed + s2.speed;
	float range = s1.range + s2.range;
	return UnitStatus(hp,hp,atk,spd, range);
}

UnitStatus operator+=(UnitStatus & s1, const UnitStatus & s2)
{
	s1 = s1 + s2;
	return s1;
}

UnitStatus operator -(const UnitStatus& s1, const UnitStatus& s2)
{
	float hp = s1.hp - s2.hp;
	float atk = s1.attack - s2.attack;
	float spd = s1.speed - s2.speed;
	float range = s1.range - s2.range;
	return UnitStatus(hp, hp, atk, spd, range);
}
UnitStatus operator -=(UnitStatus& s1, const UnitStatus& s2)
{
	s1 = s1 - s2;
	return s1;
}

bool operator ==(const UnitStatus& s1, const UnitStatus& s2)
{
	return (std::abs(s1.hp - s2.hp) <= FLT_EPSILON &&
		std::abs(s1.attack - s2.attack) <= FLT_EPSILON &&
		std::abs(s1.maxHP - s2.maxHP) <= FLT_EPSILON &&
		std::abs(s1.range - s2.range) <= FLT_EPSILON &&
		std::abs(s1.speed - s2.speed) <= FLT_EPSILON);
	
}

bool operator!=(const UnitStatus & s1, const UnitStatus & s2)
{
	return !(s1 == s2);
}
