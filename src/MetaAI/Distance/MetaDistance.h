#pragma once

#include"Base/GameUsing.h"
#include<map>
#include<functional>
class GameManager;
class MyVector3;
class Object;
//距離計算等、同じ処理が複数回動くのをデータ化して阻止する
class MetaDistance
{
public:
	//コンストラクタ
	MetaDistance();
	//デストラクタ
	~MetaDistance();
	//開始
	void Start(GameManager* manager);
	//初期化
	void Clear();

	//勢力制限付き
	UnitPtr GetNearUnitOtherInfluence(const Unit& unit,const std::function<bool(const Unit& unit)>& searchFunc = nullptr);
	UnitPtr GetNearUnitInfluence(const Unit& unit, const std::function<bool(const Unit& unit)>& searchFunc = nullptr);
	//一番近いユニットを取得
	UnitPtr GetNearUnit(const Object& obj);

	//一番近い持てるオブジェクトを返す
	LiftObjectPtr GetNearLift(const Unit& unit,const std::function<bool(const LiftObject& lift)>& searchFunc = nullptr);
	//距離を返す
	float Distance(const Object& o1, const Object& o2);
	//距離を返す
	float Distance(const LiftObject& l, UnitFactory* f);
	//一番近いユニットを返す
	UnitPtr NearUnit(const Object& obj, const UnitPtrs& units);
	//一番近い工場を返す
	FactoryPtr NearFactory(const Object& obj, const FactoryPtrs& factorys);
private:
	//一番近い持てるオブジェクトを返す
	LiftObjectPtr NearLeft(const Unit& unit,const LiftObjects& lifts);
	//距離計算
	float DistanceCalc(const Object& o1, const Object& o2);
	float DistanceCalc(const LiftObject& l, UnitFactory* f);
	//このフレーム時に検索しているか
	bool IsFindThisFrame(void* v1,void* v2);

	float GetDistance(void* d1, void* d2);
private:
	GameManager* m_manager;
	//距離保存変数
	std::map<void*, std::map<void*, float>> m_distanceData;
};