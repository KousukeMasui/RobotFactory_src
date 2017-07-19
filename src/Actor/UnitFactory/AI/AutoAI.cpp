#include "AutoAI.h"
#include"Base/VectorUtility/VectorUtility.h"
#include"Actor/Influence/AIAction/ToLiftObject/ToParts/PriorityToPartsAction.h"
#include"Actor/Influence/AIAction/ToLiftObject/ToUnit/PriorityToUnit.h"
#include"Actor/Influence/AIAction/ToFactory/Return/PriorityReturnFactory.h"
#include"Actor/Influence/AIAction/ToFactory/Heal/PriorityHealAction.h"
#include"World/World.h"
AutoAI::AutoAI(IWorld& world, const MyVector3& position, UnitFactory& factory) :
	m_cursor(position)
{
	m_shaft.Add(std::make_shared <PriorityReturnFactory>(100.0f, world, InfluenceID::PLAYER, &m_cursor, m_units,factory));
	m_shaft.Add(std::make_shared <PriorityToPartsAction>(80.0f, world, InfluenceID::PLAYER, &m_cursor, m_units));
	m_shaft.Initialize();
	m_worldSpriteManager.Set(TEXTURE_ID::AUTO);
}

AutoAI::~AutoAI()
{
}

void AutoAI::Select(const UnitPtr & unit)
{
	if (unit == nullptr) return;
	//ìoò^çœÇ›Ç»ÇÁâèú ÇªÇÍà»äOÇ»ÇÁí«â¡
	if (VectorUtility::IsExistence<UnitPtr>(m_units, unit))
		Sub(unit);
	else Add(unit);
}

void AutoAI::Update(float deltaTime)
{
	m_worldSpriteManager.Clear();
	if (m_units.empty()) return;
	m_shaft.Update(deltaTime);
	for (auto unit : m_units) {
		m_worldSpriteManager.Save(TEXTURE_ID::AUTO, unit->Position() + MyVector3(0, 40, 0), MyVector2(20, 20));
	}
}

void AutoAI::Draw() const
{
	if (m_units.empty()) return;
	m_cursor.Draw(Color(0.0f,0.0f,1.0f));
	//m_shaft.DebugDraw();

	m_worldSpriteManager.Draw();
}

const UnitPtrs AutoAI::GetUnits() const
{
	return m_units;
}

void AutoAI::Add(const UnitPtr & unit)
{
	m_units.push_back(unit);
}

void AutoAI::Sub(const UnitPtr & unit)
{
	m_units = VectorUtility::NonObjects<UnitPtr>(m_units, unit);
}
