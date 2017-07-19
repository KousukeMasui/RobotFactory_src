#include "Enemy.h"
#include"Actor\Base\IWorld.h"
#include"State/Start/StartState.h"
#include"State/Reinforcement/ReinforcementState.h"
#include"Manager\GameManager.h"
#include"Base/RoadFinder/PathFind3DUtility.h"
#include"Base/RoadFinder/PathFinder.h"
#include"Base/VectorUtility/VectorUtility.h"
#include"VerdictConstant.h"
#include"State/Start/StartState.h"
#include"Base/RoadFinder/Node/Node/NodePtr.h"
#include"Actor/Unit/AITree/Node/UnitNodeID.h"
#include"State/EnemyStateID.h"
#include"Actor/Influence/AIAction/ToFactory/Heal/PriorityHealAction.h"
#include"Actor/Influence/AIAction/ToLiftObject/ToParts/PriorityToPartsAction.h"
#include"Actor/Influence/AIAction/ToLiftObject/ToUnit/PriorityToUnit.h"
#include"Actor/Influence/AIAction/ToFactory/Return/PriorityReturnFactory.h"
#include<DxLib.h>
#include"Base/AI/Priority/Shaft/Shaft.h"
enum class EnemyActionID
{
	HEAL=0,
	DEFENCE=1,

};
Enemy::Enemy(IWorld & world) :
	Influence(world, InfluenceID::ENEMY),
	m_stateManager(),
	m_cursor({ 1288.0f, 0.0f, 824.0f })
{
	//死んでいないユニットを取得
	auto units = m_world.GetGameManager().GetUnitManager().GetFunction(m_influenceID,
		[](const Unit& unit) {
		return !unit.IsDead(); });
	UnitPtrs tmp;
	for (auto unit : units)
	{
		//物を持っていて持ち切っていない場合、あるいは置いている最中の場合除外
		if (unit->GetLift() != nullptr && (!unit->GetLift()->IsLiftEnd() || unit->NodeID() ==(int)UnitNodeID::LIFT_DOWN)) continue;
		
		tmp.push_back(unit);
	}
	m_units = tmp;
	//回復
	Shaft shaft = Shaft();
	shaft.Add(std::make_shared<PriorityHealAction>(50.0f, world, m_influenceID, &m_cursor, 0.40f, m_units));
	//戦闘中のユニットを狙う
	shaft.Add(std::make_shared<PriorityToUnit>(40.0f, world, m_influenceID, &m_cursor, m_units,
		[](const UnitPtr& unit) {
		return unit->NodeID() == (int)UnitNodeID::BATTLE;
	}));
	//資源持ち帰り
	shaft.Add(std::make_shared<PriorityReturnFactory>(100.0f, world, m_influenceID, &m_cursor, m_units));
	//後でコンストラクタから移動
	m_stateManager.Add((int)EnemyStateID::START, std::make_shared<StartState>(world, shaft, &m_cursor,m_units));
	m_stateManager.Add((int)EnemyStateID::REINFORCEMENT, std::make_shared<ReinforcementState>(world, shaft, &m_cursor,m_units));
	m_stateManager.SetState((int)EnemyStateID::START);
}

Enemy::~Enemy()
{
}

void Enemy::Update(float deltaTime)
{
	//工場がない場合、ゲーム終了なので
	if (m_world.GetGameManager().GetFactoryManager().GetVector(m_influenceID).empty()) return;
	m_cursor.Scale(MyVector3(20, 1, 20));
	//死んでいないユニットを取得
	m_units = m_world.GetGameManager().GetUnitManager().GetFunction(m_influenceID, 
		[](const Unit& unit) {return !unit.IsDead(); });
	m_stateManager.Update(deltaTime);
}

void Enemy::Draw() const
{
	m_cursor.Draw(Color(1.0f,0.0f,0.0f));

}

LerpCursor& Enemy::Cursor()
{
	return m_cursor;
}
