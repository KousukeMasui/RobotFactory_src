#pragma once
#include"Object/Object.h"
#include"Model/Model/Model.h"
#include"Actor/Influence/InfluenceID.h"
#include"../Status/FactoryStatus.h"
struct Sphere;
class IWorld;
class UnitFactory;
//工場の回復クラス
class FactoryHeal : public Object
{
public:
	FactoryHeal(IWorld& world,UnitFactory* factory);
	~FactoryHeal();

	void Update(float deltaTime);
	void Draw() const;

	void ChangeColor(InfluenceID id);

	void StatusUp(const FactoryStatus& status);

	Sphere GetSphere() const;
private:
	IWorld& m_world;
	UnitFactory* m_factory;
	Model m_model;
	Color m_color;

	int m_power;
	float m_range;
	const float m_defaultInterval;
	float m_timer;//回復タイマz
};