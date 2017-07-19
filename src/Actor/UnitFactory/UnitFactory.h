#pragma once

#include<string>
#include"Math/Shapes/3D/Ray/Ray.h"
class IWorld;
class Unit;
class UnitStatus;
struct Sphere;
struct Capsule;
struct Line3D;
#include"Math/Collision/HitInfo/HitInfo.h"
#include"Math/Point2/Point2.h"
#include"Status\FactoryStatus.h"
#include"Parameter/FactoryParam.h"
#include"Manager/FactoryManager.h"
#include"Model/Model/Model.h"
#include"AI/AutoAI.h"
#include"Heal/FactoryHeal.h"
class UnitFactory
{
public:
	UnitFactory(IWorld& world, InfluenceID influence,const MyVector3& position,FactoryManager& manager);
	~UnitFactory();

	//勢力の変更
	void ChangeInfluence(InfluenceID influence);
	//回復を返す
	const FactoryHeal& GetHeal() const;


	void Update(float deltaTime);
	//無所属時にのみ行う更新関数
	void NonInfluenceUpdate(float deltaTime);
	void Draw() const;

	bool IsDelete();
	FactoryParam& GetParam();
	bool IsCollide(const MyVector3& position);
	bool IsCollide(const Sphere& other,HitInfo& hit) const;
	bool IsCollide(const Capsule& caspule) const;
	HitInfo IsCollide(const Line3D& line) const;
	void Collide(Unit& other,HitInfo& hit);

	//資源を置く等の範囲に入ったらtrue
	bool IsCollide(const Unit& unit);
	void Collide(Unit& unit);
	//資源数を+する
	void PartsCount(int add);
	int PartsCount() const;//資源数の取得

	FactoryStatus& Status();

	void StatusUp(FactoryStatusID id);
	//生成開始
	void CreateStart(const UnitStatus& status);
	//生成処理
	void Create(const UnitStatus& status);

	//ダメージ関数
	void Damage(int attack, InfluenceID influence);

	//自分の周りのpointを返す
	std::vector<Point2> GetPoints() const;
	void AddTarget(Point2 target);
	void SubTarget(Point2 target);
	std::vector<Point2> GetTargeted() const;

	//自分の工場のnodeの2を全て取得する
	std::vector<Point2> MyPoints() const;

	void SelectUnit(const UnitPtr& unit);
	const UnitPtrs GetAutoUnits() const;
	void Heal(float power);//回復関数
private:

	//周りのpointを求める
	void PointsSet();

private:
	IWorld& m_world;
	FactoryManager& m_manager;
	StaticModel m_model;
	Point2 m_point;
	//生成するユニットのステータス
	FactoryStatus m_status;

	FactoryParam m_param;
	//周りのpoint
	std::vector<Point2> m_circlePoints;
	//周りのpoint
	std::vector<Point2> m_myPoints;
	//現在、エネミーのユニットが狙っているPoint配列
	std::vector<Point2> m_targetedPoints;


	FactoryHeal m_heal;

	AutoAI m_autoAI;
	//生成するユニットのステータス
	std::list<UnitStatus> m_createStatus;
};