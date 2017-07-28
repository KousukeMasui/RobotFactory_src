#pragma once
class Unit;
class UnitStatus;
class IWorld;
struct FactoryParam;
class RootFind;
#include"Math/Vector/MyVector3.h"
#include"Math/Shapes/3D/Sphere/Sphere.h"
#include"Base/GameUsing.h"
#include<list>
class UnitCreate {
public:
	//コンストラクタ
	UnitCreate(IWorld& world,RootFind& find,FactoryParam& param);
	//デストラクタ
	~UnitCreate();
	//更新
	void Update();
	//当たり判定　ここに触れているユニットがいたら生成できなくする
	bool IsCollide();
	//生成命令
	void Create(const UnitStatus& status);
private:
	//実際の生成処理
	void Create();
private:
	IWorld& m_world;
	//球の当たり判定
	Sphere m_sphere;
	//生成するユニットのステータス
	std::list<UnitStatus> m_status;
	FactoryParam& m_param;
	RootFind& m_find;
	UnitPtr m_createUnit;
};