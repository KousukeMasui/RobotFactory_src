#include "ToUnit.h"
#include"Actor/Unit/Unit.h"
#include"CSVReader/CSVData.h"
#include"Manager/GameManager.h"
#include"../Base/UnitMessageID.h"
ToUnit::ToUnit(GameManager& manager,Unit& unit):
	m_myUnit(unit),
	m_manager(manager),
	m_moveDistance(manager.GetCSV().Get_F(CSVData::CSV_DATA_ID::UNIT_ATTACK_RANGE,1))
{
	
}

ToUnit::~ToUnit()
{
}

void ToUnit::SetTarget(const UnitPtr & target)
{
	m_targetUnit = target;
	ToUnitRoot();
}

void ToUnit::Update()
{
	if (m_targetUnit == nullptr) return;
	//ユニットが停止した際に目的ユニットと一定距離まで近づいていたら処理終了
	if (!m_myUnit.Agent().IsMove() && m_manager.GetMetaAI().Distance().Distance(*m_targetUnit, m_myUnit) <= m_moveDistance) {
		m_targetUnit = nullptr;
		return;
	}
	//一定以上動いていない場合は目的地を更新しない
	if (MyVector3::Distance(m_prevPosition, m_targetUnit->Position()) <= m_moveDistance) return;


	//経路探索
	ToUnitRoot();
}

void ToUnit::ToUnitRoot()
{
	m_myUnit.Agent().SetRoot(m_targetUnit->Position());
	m_prevPosition = m_targetUnit->Position();
}
