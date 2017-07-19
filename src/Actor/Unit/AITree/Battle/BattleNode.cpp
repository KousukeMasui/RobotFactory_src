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
	//���݂̃��[�V�������U���̏ꍇ
	if (m_unit.GetModel().GetAnimationID() == (int)UnitAnimationID::ATTACK)
		m_unit.GetModel().SetAnimationTime(0.0f);//�A�j���[�V���������Z�b�g

}
void BattleNode::End()
{
	if (m_target != nullptr)//���j�b�g��_���ꍇ
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
	//���������Ă���ꍇ�퓬�ɓ���Ȃ�
	if (m_unit.GetLift() != nullptr) return false;
	//��ԋ߂������Ă郆�j�b�g���擾
	m_target = m_world.GetMetaAI().Distance().GetNearUnitOtherInfluence(m_unit, 
		[&](const Unit& unit) {return !unit.IsDead() && unit.GetInfluence() != m_unit.GetInfluence(); });
	
	if (m_target != nullptr && m_world.GetMetaAI().Distance().Distance(m_unit,*m_target) <= MyVector3(40,40).Length())//��ԋ߂����j�b�g�Ƃ̋��������͈͂��Ȃ���������U����Ԃ�
	{
		m_targetFactory = nullptr;
		return true;
	}
	//�������ȊO�Ŏ����̐��͈ȊO�̍H����擾
	auto otherFactorys = m_world.GetGameManager().GetFactoryManager().GetFunction(
		[&](const FactoryParam& param)
	{
		return param.influence != InfluenceID::NONE && param.influence != m_unit.GetInfluence();
	});

	//�H���T��
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
	
	//���݂�rotate�ƓG�܂ł̕�����10�x�ȓ��ɂȂ�����
	if (m_unit.LerpToVelocity(targetPosition - m_unit.Position()))
	{
		//�U�����[�V�����̍Đ�
		m_unit.GetModel().ChangeAnimation((int)UnitAnimationID::ATTACK, false);
		m_unit.GetModel().Update(0.0f, m_unit.GetPose());
	}
	else//10�x���傫���ꍇ�A�A�j���[�V�������Đ����Ă��Ȃ��̂ő������^�[��
		return;
}

bool BattleNode::SetIsEnd()
{
	return ((m_unit.GetModel().GetAnimationID() == UnitAnimationID::ATTACK && m_unit.GetModel().GetAnimationTime() >= 34.53f)||
		(m_target != nullptr&& m_target->NodeID()==(int)UnitNodeID::DEAD)||//����̃��j�b�g�����񂾏ꍇ
		//(m_world.GetMetaAI().Distance().Distance(*m_target,m_unit) <=0.0f) ||//����̃��j�b�g������Ă������ꍇ
		(m_targetFactory != nullptr && m_targetFactory->GetParam().influence == m_unit.GetInfluence()) ||//�H��̐��͂��ς�����ꍇ
			m_unit.IsMove()//�ړ��J�n������
			);
}
