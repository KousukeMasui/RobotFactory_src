#pragma once
#include"Base/GameUsing.h"
#include<vector>
#include"Math/Vector/MyVector3.h"
//ユニットを複数同時に動かすためのクラス
class GroupUnits {
public:
	//コンストラクタ
	GroupUnits();
	//デストラクタ
	~GroupUnits();
	//追加
	void AddUnit(const UnitPtr& unit);
	//命令した際の目的地
	void Order(const MyVector3& targetPosition);
	//更新
	void Update(float deltaTime);
private:
	//先頭ユニットの選別
	UnitPtr CheckCaptain();

private:
	//グループのユニット達
	std::vector<UnitPtr> m_units;
	//命令の先頭になるユニット
	UnitPtr m_captainUnit;

	//目的地
	MyVector3 m_targetPosition;
	//移動開始するか
	bool m_isMoveStart;
};