#include "GroupUnits.h"

GroupUnits::GroupUnits():
	m_captainUnit(nullptr),
	m_isMoveStart(false)
{
}

GroupUnits::~GroupUnits()
{
}

void GroupUnits::AddUnit(const UnitPtr & unit)
{
	m_units.push_back(unit);
}

void GroupUnits::Order(const MyVector3 & targetPosition)
{
	m_isMoveStart = true;
	m_targetPosition = targetPosition;
}

void GroupUnits::Update(float deltaTime)
{
	if (!m_isMoveStart) return;
}

UnitPtr GroupUnits::CheckCaptain()
{
	if (m_units.empty()) return nullptr;//ãÛÇÃèÍçánull
	if (m_units.size()<=1) return m_units.front();//àÍÇ¬ÇÃèÍçáÇªÇÃóvëfÇï‘Ç∑

}
