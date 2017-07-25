#pragma once
#include"Base/GameUsing.h"
#include"Math/Vector/MyVector3.h"
class GameManager;
//ユニットを追従させる
//敵とプレイヤーユニットの移動で少し変更するので継承で実装
class ToUnit {
public:
	ToUnit(GameManager& manager,Unit& unit);
	~ToUnit();

	//目的ユニットを設定
	void SetTarget(const UnitPtr& target);
	//更新
	void Update();
private:
	//目的ユニットまで移動する経路を計算
	void ToUnitRoot();
private:
	//自分のユニット
	Unit& m_myUnit;
	//マネージャ
	GameManager& m_manager;
	//どれくらい移動されたら再度計算するか
	const float m_moveDistance;
	//追従するユニット
	UnitPtr m_targetUnit;
	//追従するユニットの前の位置
	MyVector3 m_prevPosition;
};