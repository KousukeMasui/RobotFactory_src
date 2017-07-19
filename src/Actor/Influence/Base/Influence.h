#pragma once
class IWorld;
#include<forward_list>
#include"Base/GameUsing.h"
#include"../InfluenceID.h"
//Player,Enemyの親クラス
class Influence
{
public:
	Influence(IWorld& world, InfluenceID id);
	~Influence();
	//自軍ユニットを全て取得
	UnitPtrs GetUnits();
	virtual void Update(float deltaTime) = 0;
	virtual void Draw() const = 0;
	//現在は削除予定は無いのでfalseを返す
	bool IsDelete() { return false; }
protected:
	IWorld& m_world;
	const InfluenceID m_influenceID;
};