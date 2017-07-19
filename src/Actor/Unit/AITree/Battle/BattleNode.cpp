#include "BattleNode.h"
#include"Math/Collision/Model/ModelCollision.h"
#include"../../Unit.h"
#include"Manager\GameManager.h"
#include"Actor\UnitFactory\UnitFactory.h"
#include"Math/Converter.h"
#include"Math/MyMath.h"
#include"../Node/UnitNodeID.h"
#include"../../Base/UnitMessageID.h"
#include"../../Base/UnitAnimationID.h"
#include"World/World.h"
BattleNode::BattleNode(IWorld& world, Unit & unit):
	UnitAINode(unit,UnitNodeID::BATTLE),
	m_world(world)
{
}

BattleNode::~BattleNode()
{
}

void BattleNode::Start()
{
	m_isEnd = false;
	//現在のモーションが攻撃の場合
	if (m_unit.GetModel().GetAnimationID() == (int)UnitAnimationID::ATTACK)
		m_unit.GetModel().SetAnimationTime(0.0f);//アニメーションをリセット

}
void BattleNode::End()
{
	if (m_target != nullptr)//ユニットを狙う場合
	{
		m_target->Message((int)UnitMessageID::DAMAGE, &m_unit.GetStatus().attack);
	}
	else
	{
		m_targetFactory->Damage(m_unit.GetStatus().attack, m_unit.GetInfluence());
	}
}

bool BattleNode::Branch()
{
	//物を持っている場合戦闘に入らない
	if (m_unit.GetLift() != nullptr) return false;
	//一番近い生きてるユニットを取得
	m_target = m_world.GetMetaAI().Distance().GetNearUnitOtherInfluence(m_unit, 
		[&](const Unit& unit) {return !unit.IsDead() && unit.GetInfluence() != m_unit.GetInfluence(); });
	
	if (m_target != nullptr && m_world.GetMetaAI().Distance().Distance(m_unit,*m_target) <= MyVector3(40,40).Length())//一番近いユニットとの距離が一定範囲いないだったら攻撃状態へ
	{
		m_targetFactory = nullptr;
		return true;
	}
	//無所属以外で自分の勢力以外の工場を取得
	auto otherFactorys = m_world.GetGameManager().GetFactoryManager().GetFunction(
		[&](const FactoryParam& param)
	{
		return param.influence != InfluenceID::NONE && param.influence != m_unit.GetInfluence();
	});

	//工場を探す
	for (auto enemyFactory : otherFactorys)
	{
		if (enemyFactory->IsCollide(m_unit.Position()))
		{
			m_targetFactory = enemyFactory;
			m_target = nullptr;
			return true;
		}
	}
	return false;
}

void BattleNode::OnUpdate(float deltaTime)
{

	MyVector3 targetPosition;
	if (m_target == nullptr)
	{
		targetPosition = m_targetFactory->GetParam().Position();
	}
	else
	{
		targetPosition = m_target->Position();
	}
	
	//現在のrotateと敵までの方向が10度以内になったら
	if (m_unit.LerpToVelocity(targetPosition - m_unit.Position()))
	{
		//攻撃モーションの再生
		m_unit.GetModel().ChangeAnimation((int)UnitAnimationID::ATTACK, false);
		m_unit.GetModel().Update(0.0f, m_unit.GetPose());
	}
	else//10度より大きい場合、アニメーションを再生していないので早期リターン
		return;
}

bool BattleNode::SetIsEnd()
{
	return ((m_unit.GetModel().GetAnimationID() == UnitAnimationID::ATTACK && m_unit.GetModel().GetAnimationTime() >= 34.53f)||
		(m_target != nullptr&& m_target->NodeID()==(int)UnitNodeID::DEAD)||//相手のユニットが死んだ場合
		//(m_world.GetMetaAI().Distance().Distance(*m_target,m_unit) <=0.0f) ||//相手のユニットが離れていった場合
		(m_targetFactory != nullptr && m_targetFactory->GetParam().influence == m_unit.GetInfluence()) ||//工場の勢力が変わった場合
			m_unit.IsMove()//移動開始したら
			);
}
