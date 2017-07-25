#include "LiftDownNode.h"
#include"World/World.h"
#include"Manager\GameManager.h"
#include"Actor\UnitFactory\UnitFactory.h"
#include"Base/RoadFinder/PathFind3DUtility.h"
#include"Base/VectorUtility/VectorUtility.h"
#include"Base/UtilTemplate/UtilTemplate.h"
#include"Actor\Influence\Enemy\VerdictConstant.h"
#include"../Node/UnitNodeID.h"
#include"../../Base/UnitAnimationID.h"
#include"UI/Sprite\BillBoard\BillBoard.h"
#include"Actor/Unit/Base/UnitMessageID.h"
LiftDownNode::LiftDownNode(IWorld & world, Unit& unit):
	UnitAINode(unit,UnitNodeID::LIFT_DOWN),
	m_world(world)
{
}

LiftDownNode::~LiftDownNode()
{
}

void LiftDownNode::Start()
{
	//�����~�낷�A�j���[�V����
	m_unit.GetModel().ChangeAnimation((int)UnitAnimationID::LIFT_DOWN, false);
	m_unit.GetModel().Update(0.0f, m_unit.GetPose());//�A�j���[�V�����݂̂����ւ���
	m_isEnd = false;
}

void LiftDownNode::End()
{
	m_unit.GetLift()->LiftEnd();
	//����̓G�l�~�[�̂ݓo�^�Ȃ̂ł����ɒ��ł�����
	m_world.GetGameManager().GetMetaAI().Overlap().Remove(m_unit.GetLift());
	//�߂��ɍH�ꂪ����ꍇ
	if (m_factory != nullptr)
	{
		m_unit.GetLift()->LiftDown(m_factory);
	}
	//������
	m_unit.Message((int)UnitMessageID::LIFT,nullptr);
	m_world.GetBillBoardManager().Find(BillBoardID::HAVE_UI, m_unit.PositionPtr())->Delete();
}

bool LiftDownNode::Branch()
{
	FactoryPtrs factorys;

	//�����͂̍H��ŐG��Ă���H����擾
	for (auto factory : m_world.GetGameManager().GetFactoryManager().GetVector(m_unit.GetInfluence()))
	{
		if (factory->IsCollide(m_unit) || VectorUtility::IsExistence<Point2>(factory->GetPoints(), PathFind3DUtility::ToNodePoint2(m_unit.Position())))
			factorys.push_back(factory);
	}
	//��ԋ߂��H����擾
	m_factory = VectorUtility::GetMostObject<FactoryPtr>(factorys, [&](const FactoryPtr& f1, const FactoryPtr& f2) {
		return UtilTemplate::GetNearObject<FactoryPtr>(m_unit.Position(), f1, f2, [](const FactoryPtr& f) {return f->GetParam().Position(); });
	});
	//�H�ꂪ����ꍇ�Atrue
	if (m_factory != nullptr) return true;

	//�Ⴄ���͂̃��j�b�g�̒��ň�ԋ߂����j�b�g���擾
	auto nearEnemy = m_world.GetGameManager().GetMetaAI().Distance().GetNearUnitOtherInfluence(m_unit, [](const Unit& unit) {return !unit.IsDead(); });
	//��苗���ȓ��Ȃ�
	return (nearEnemy != nullptr && m_world.GetGameManager().GetMetaAI().Distance().Distance(*nearEnemy, m_unit) <= BattleDistance);
}

void LiftDownNode::OnUpdate(float deltaTime)
{
	m_unit.GetLift()->LiftUp(m_unit);
}

bool LiftDownNode::SetIsEnd()
{
	return m_unit.GetModel().IsAnimationEnd();
}
