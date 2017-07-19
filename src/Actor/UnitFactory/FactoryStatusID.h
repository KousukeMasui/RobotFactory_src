#pragma once


enum class FactoryStatusID
{
	UNIT_HP = 0,	//ユニットの体力
	UNIT_ATK,	//ユニットの攻撃力
	UNIT_SPD,	//ユニットの速度
	HEAL_POWER,	//工場の回復力
	HEAL_RANGE,	//回復範囲
	CREATE,		//ユニット生成
};