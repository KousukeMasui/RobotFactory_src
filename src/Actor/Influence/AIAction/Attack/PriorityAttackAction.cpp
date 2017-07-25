#include "PriorityAttackAction.h"
#include"../ToLiftObject/ToUnit/PriorityToUnit.h"
#include"../ToFactory/PriorityToFactory.h"
#include"World/World.h"
#include"Actor/Unit/Unit.h"
#include"Actor/Unit/AITree/Node/UnitNodeID.h"
#include"../Base/State/OrderFactory/OrderFactoryState.h"
#include"../Base/State/ToUnit/ToUnitState.h"
#include"../Base/CursorStateID.h"
#include"Actor/UnitFactory/UnitFactory.h"
PriorityAttackAction::PriorityAttackAction(float priority, IWorld & world, InfluenceID id, LerpCursor * cursor, UnitPtrs & units):
	GamePriorityAction(priority,world,id,cursor,units)
{
}

void PriorityAttackAction::Initialize()
{
	m_isEnd = true;
	//�񕜔͈͂ɂ��郆�j�b�g�ɍU�����Ă���
	m_shaft.Add(std::make_shared<PriorityToUnit>(100.0f, m_world, m_influenceID, m_cursor, m_orderUnits,
		[&](const UnitPtr& unit)
	{
		return unit->GetSphere().IsCollide(m_targetFactory->GetHeal().GetSphere());
	}));
	m_shaft.Add(std::make_shared<PriorityToFactory>(10.0f, m_world, m_influenceID, m_cursor, m_orderUnits, &*m_targetFactory));

	m_shaft.Initialize();
}

void PriorityAttackAction::Update(float deltaTime)
{
	auto units = m_orderUnits;
	m_orderUnits.clear();
	for (auto unit : units)
	{
		if (!unit->Agent().IsMove()) m_orderUnits.push_back(unit);
	}

	m_shaft.Update(deltaTime);

	m_isEnd = m_orderUnits.empty();
}

void PriorityAttackAction::End()
{
}

void PriorityAttackAction::Draw() const
{
}

float PriorityAttackAction::OnPriority()
{
	//�퓬�ɎQ���ł��郆�j�b�g��I��
	for (auto unit : m_units)
	{
		if (unit->GetLift() != nullptr) continue;//���������Ă���
		if (unit->Agent().IsMove()) continue;//�ړ���
		if (unit->GetParam().NodeID() == (int)UnitNodeID::BATTLE) continue;//�퓬��
		m_orderUnits.push_back(unit);
	}
	float factoryDefence;
	m_targetFactory = GetWeakFactory(factoryDefence);
	//�_����H�ꂪ�Ȃ��ꍇ�A���̍s���͍s��Ȃ�
	if (m_targetFactory == nullptr) return -1;
	//���v�X�e�[�^�X���v�Z
	float status = 0.0f;
	for (auto unit : m_orderUnits)
	{
		status += unit->GetStatus().Status(UNIT_STATUS_ID::HP) + unit->GetStatus().Status(UNIT_STATUS_ID::ATK);
	}
	//�H��̃X�e�[�^�X�̕��������ꍇ�@���������l��Ԃ�
	if (factoryDefence >= status) return -100000.0f;

	return m_distancePriority / 100 - (status - factoryDefence);
}

FactoryPtr PriorityAttackAction::GetWeakFactory(float& power)
{
	auto myFactorys = m_world.GetGameManager().GetFactoryManager().GetVector(m_influenceID);
	//�����̍H��ɋ߂��H��݂̂��擾
	auto otherFactorys = m_world.GetGameManager().GetFactoryManager().GetOtherFunctionPtr(m_influenceID,
		[&](const FactoryPtr& factory) {
		for (auto f : myFactorys)
		{
			//�����̍H��̉񕜔͈͂̔{�ȓ��̋����ɂ���H����擾
			if (factory->IsCollide(Sphere(f->GetHeal().GetSphere().m_center, f->GetHeal().GetSphere().m_radius * 2.0f),HitInfo()))
				return true;
		}
		return false;
	});
	//����ɍH�ꂪ�Ȃ��ꍇ
	if (otherFactorys.empty()) return nullptr;

	FactoryPtr result;
	float min = FLT_MAX;
	for (auto factory : otherFactorys)
	{
		//�񕜔͈͓��̃��j�b�g��h�q���Ƃ��Ă݂Ȃ�
		auto units = m_world.GetGameManager().GetUnitManager().GetOtherFunction(m_influenceID, 
			[&](const Unit& unit) {
			return unit.GetSphere().IsCollide(factory->GetHeal().GetSphere());
		});
		float status = 0.0f;
		for (auto unit : units)
		{
			status += unit->GetStatus().Status(UNIT_STATUS_ID::HP) + unit->GetStatus().Status(UNIT_STATUS_ID::ATK);
		}
		if (min >= status)
		{
			result = factory;
			min = status;
		}
	}
	power = min;
	return result;
}
