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
	m_frontStatusAI(),
	m_backStatusAI(),
	m_shaft(shaft),
	m_cursor(cursor)
{
	//資源回収
	m_shaft.Add(std::make_shared<PriorityToPartsAction>(30.0f, world, InfluenceID::ENEMY, cursor, units));
	//ユニット回収
	m_shaft.Add(std::make_shared<PriorityToDeadUnit>(25.0f, world, InfluenceID::ENEMY, cursor, units));
	//攻撃
	m_shaft.Add(std::make_shared<PriorityAttackAction>(10.0f, m_world, InfluenceID::ENEMY, cursor, units));

	m_shaft.Initialize();
}

ReinforcementState::~ReinforcementState()
{
}

void ReinforcementState::Initialize()
{
	//ステータスの設定
	std::vector<FactoryStatusID> status;
	//前線の設定
	status.push_back(FactoryStatusID::HEAL_RANGE);
	status.push_back(FactoryStatusID::HEAL_POWER);
	status.push_back(FactoryStatusID::CREATE);
	status.push_back(FactoryStatusID::UNIT_ATK);
	status.push_back(FactoryStatusID::UNIT_SPD);
	status.push_back(FactoryStatusID::UNIT_HP);
	m_frontStatusAI.SetPriority(status);
	status.clear();
	//後ろの設定
	status.push_back(FactoryStatusID::UNIT_HP);
	status.push_back(FactoryStatusID::CREATE);
	status.push_back(FactoryStatusID::UNIT_ATK);
	status.push_back(FactoryStatusID::UNIT_SPD);
	m_backStatusAI.SetPriority(status);
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
	return  false;
}

void ReinforcementState::PowerUp()
{
	//FactoryPtrs front, back;
	//AIAction::Front_Back_Check(m_factorysMap[InfluenceID::ENEMY], 
	//	m_factorysMap[InfluenceID::PLAYER],
	//	front, back);
	////強化処理
	m_frontStatusAI.PowerUp(m_world.GetGameManager().GetFactoryManager().GetVector(InfluenceID::ENEMY));
	//m_backStatusAI->PowerUp(back);
}