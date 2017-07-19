#include "FactoryHeal.h"
#include"World/World.h"
#include"../UnitFactory.h"
#include"Math/Shapes/3D/Sphere/Sphere.h"
#include"Actor\Unit/Base\UnitMessageID.h"
FactoryHeal::FactoryHeal(IWorld& world, UnitFactory* factory):
	Object(factory->GetParam().Position() + MyVector3(0, 2, 0),MyMatrix4::Identity()),
	m_world(world),
	m_factory(factory),
	m_model(MODEL_ID::CIRCLE),
	m_range(20.0f + 90.0f),
	m_power(1),
	m_defaultInterval(180.0f),
	m_timer(0.0f)
{
	ChangeColor(factory->GetParam().influence);
}

FactoryHeal::~FactoryHeal()
{
}

void FactoryHeal::Update(float deltaTime)
{
	m_timer += deltaTime;
	if (m_timer >= m_defaultInterval)
	{
		m_timer = 0.0f;
		//回復力をfloatに
		float p = (float)m_power;
		//回復処理
		m_world.GetGameManager().GetUnitManager().Message(m_factory->GetParam().influence, (int)UnitMessageID::HEAL,
			[&](UnitPtr unit) {
			if (unit->IsDead()) return;//死んでいるユニットは除外する
			if (GetSphere().IsCollide(unit->GetSphere()))//回復範囲内
				unit->Message((int)UnitMessageID::HEAL, &p);
		});
		m_factory->Heal(p);
	}
}

void FactoryHeal::Draw() const
{
	m_model.SetMaterialColor(0,m_color);

	m_model.Draw(m_position, MyVector3(m_range, 1, m_range), MyVector3::Zero());
}

void FactoryHeal::ChangeColor(InfluenceID id)
{
	//範囲のモデルの色を変える
	m_color = Color(id == InfluenceID::ENEMY, id == InfluenceID::PLAYER, 0.0f, 1.0f);
}

void FactoryHeal::StatusUp(const FactoryStatus & status)
{
	m_range = status.status.at(FactoryStatusID::HEAL_RANGE) * 20.0f + 90.0f;
	m_power = status.status.at(FactoryStatusID::HEAL_POWER);
}

Sphere FactoryHeal::GetSphere() const
{
	return Sphere(m_position, m_range);
}
