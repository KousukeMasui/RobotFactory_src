#include "StartState.h"
#include"Base/RoadFinder/PathFinder.h"
#include"Base/RoadFinder/PathFind3DUtility.h"
#include"Base/VectorUtility/VectorUtility.h"
#include"../EnemyStateID.h"
#include"Cursor\LerpCursor.h"
#include"World/World.h"
#include"Actor/Influence/AIAction/ToFactory/PriorityToFactory.h"
#include"Actor/Influence/AIAction/ToLiftObject/ToParts/PriorityToPartsAction.h"
StartState::StartState(IWorld & world, const Shaft & shaft, LerpCursor* cursor, UnitPtrs& units):
	m_world(world),
	m_shaft(shaft),
	m_cursor(cursor),
	m_statusAI(std::make_shared<FactoryStatusAI>())
{
	//無所属工場に向かう
	m_shaft.Add(std::make_shared<PriorityToFactory>(200.0f, world, InfluenceID::NONE, cursor, units));
	//資源回収
	m_shaft.Add(std::make_shared<PriorityToPartsAction>(30.0f, world, InfluenceID::ENEMY, cursor, units));
	
	m_shaft.Initialize();
}

StartState::~StartState()
{
}

void StartState::Initialize()
{
	//強化するステータスを設定
	std::vector<FactoryStatusID> status;

	//status.push_back(FactoryStatusID::HEAL_RANGE);
	status.push_back(FactoryStatusID::UNIT_SPD);
	status.push_back(FactoryStatusID::CREATE);
	m_statusAI->SetPriority(status);
}

void StartState::Update(float deltaTime)
{
	m_statusAI->PowerUp(m_world.GetGameManager().GetFactoryManager().GetVector(InfluenceID::ENEMY));

	m_shaft.Update(deltaTime);
}

void StartState::End()
{
}

int StartState::Next()const
{
	return (int)EnemyStateID::REINFORCEMENT;
}

bool StartState::IsEnd()const
{
	//無所属の工場が無くなったら
	return m_world.GetGameManager().GetFactoryManager().GetVector(InfluenceID::NONE).empty();
}