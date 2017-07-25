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
	//���j�b�g����~�����ۂɖړI���j�b�g�ƈ�苗���܂ŋ߂Â��Ă����珈���I��
	if (!m_myUnit.Agent().IsMove() && m_manager.GetMetaAI().Distance().Distance(*m_targetUnit, m_myUnit) <= m_moveDistance) {
		m_targetUnit = nullptr;
		return;
	}
	//���ȏ㓮���Ă��Ȃ��ꍇ�͖ړI�n���X�V���Ȃ�
	if (MyVector3::Distance(m_prevPosition, m_targetUnit->Position()) <= m_moveDistance) return;


	//�o�H�T��
	ToUnitRoot();
}

void ToUnit::ToUnitRoot()
{
	m_myUnit.Agent().SetRoot(m_targetUnit->Position());
	m_prevPosition = m_targetUnit->Position();
}
