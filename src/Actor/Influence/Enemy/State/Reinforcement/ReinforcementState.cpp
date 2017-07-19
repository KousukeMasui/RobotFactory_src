#include "ReinforcementState.h"

#include"World\World.h"
#include"Manager/GameManager.h"
#include<set>
#include"Actor/Influence/Enemy/FactoryStatusAI/FactoryStatusAI.h"
#include"Base/VectorUtility/VectorUtility.h"
#include"Actor/Unit/AITree/Node/UnitNodeID.h"
#include"../EnemyStateID.h"
#include"Actor/Influence/AIAction/ToFactory/PriorityToFactory.h"
#include"Actor/Influence/AIAction/ToLiftObject/ToParts/PriorityToPartsAction.h"
#include"Actor/Influence/AIAction/ToLiftObject/ToUnit/PriorityToDeadUnit.h"
#include"Actor/Influence/AIAction/Attack/PriorityAttackAction.h"
ReinforcementState::ReinforcementState(IWorld & world, const Shaft & shaft, LerpCursor * cursor, UnitPtrs & units):
	IState(),
	m_world(world),
	m_frontStatusAI(std::make_shared<FactoryStatusAI>()),
	m_backStatusAI(std::make_shared<FactoryStatusAI>()),
	m_shaft(shaft),
	m_cursor(cursor)
{
	//�������
	m_shaft.Add(std::make_shared<PriorityToPartsAction>(30.0f, world, InfluenceID::ENEMY, cursor, units));
	//���j�b�g���
	m_shaft.Add(std::make_shared<PriorityToDeadUnit>(25.0f, world, InfluenceID::ENEMY, cursor, units));
	//�U��
	m_shaft.Add(std::make_shared<PriorityAttackAction>(10.0f, m_world, InfluenceID::ENEMY, cursor, units));

	m_shaft.Initialize();
}

ReinforcementState::~ReinforcementState()
{
}

void ReinforcementState::Initialize()
{

	//�X�e�[�^�X�̐ݒ�
	std::vector<FactoryStatusID> status;
	//�O���̐ݒ�
	status.push_back(FactoryStatusID::CREATE);
	status.push_back(FactoryStatusID::HEAL_RANGE);
	status.push_back(FactoryStatusID::HEAL_POWER);
	m_frontStatusAI->SetPriority(status);
	status.clear();
	//���̐ݒ�
	status.push_back(FactoryStatusID::UNIT_HP);
	status.push_back(FactoryStatusID::CREATE);
	status.push_back(FactoryStatusID::UNIT_ATK);
	status.push_back(FactoryStatusID::UNIT_SPD);
	m_backStatusAI->SetPriority(status);
}

void ReinforcementState::Update(float deltaTime)
{
	m_shaft.Update(deltaTime);
	PowerUp();
}

void ReinforcementState::End()
{
}

int ReinforcementState::Next()const
{
	return (int)EnemyStateID::REINFORCEMENT;
}

bool ReinforcementState::IsEnd()const
{
	//���݂̃��j�b�g�̃X�e�[�^�X�ƃv���C���[�̃X�e�[�^�X�Ŕ�r���ĕ]��
	UnitStatus my(0, 0, 0, 0, 0);
	UnitStatus player(0, 0, 0, 0, 0);
	m_world.GetGameManager().GetUnitManager().Function(
		[&](UnitPtr unit)
	{
		//����ł��郆�j�b�g�����O
		if (unit->GetParam().NodeID() == (int)UnitNodeID::DEAD) return;

		if (unit->GetInfluence() == InfluenceID::PLAYER)
			player += unit->GetStatus();
		else
			my + unit->GetStatus();
	});

	float myDef = my.hp / player.attack;
	float playerDef = player.hp / my.attack;
	return  false;// myDef > playerDef;
}

void ReinforcementState::PowerUp()
{
	//FactoryPtrs front, back;
	//AIAction::Front_Back_Check(m_factorysMap[InfluenceID::ENEMY], 
	//	m_factorysMap[InfluenceID::PLAYER],
	//	front, back);
	////��������
	m_frontStatusAI->PowerUp(m_world.GetGameManager().GetFactoryManager().GetVector(InfluenceID::ENEMY));
	//m_backStatusAI->PowerUp(back);
}