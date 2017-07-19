#include "PartsCreater.h"
#include"Math/MyMath.h"
#include"Actor\Base\IWorld.h"
#include"Actor/Base/ActorGroup.h"
#include"Actor\Parts\Parts.h"
#include"Manager\GameManager.h"
#include"Base/RoadFinder/PathFind3DUtility.h"
#include"Base/RoadFinder/Map/FieldMap.h"
#include"Base/VectorUtility/VectorUtility.h"
#include"Actor/UnitFactory/UnitFactory.h"
const MyVector3 MinCreatePosition = MyVector3(0, 0, 0);
const MyVector3 MaxCreatePosition = MyVector3(1600, 0, 1600);

const int MAX = 20;

PartsCreater::PartsCreater(IWorld & world):
	Actor3D(world,"",MyVector3::Zero()),
	m_createInterval(MyMath::Random(60.0f, 180.0f))
{
}

PartsCreater::~PartsCreater()
{
}

void PartsCreater::OnUpdate(float deltaTime)
{
	m_createInterval -= deltaTime;
	//��萔�ȏ㎑��������ƃW���}+�d���Ȃ�̂ő����Ȃ肷���Ȃ��悤�ɕ␳
	//if (m_world->GetMetaAI().LiftObjectSize() >= MAX) return;
	if (m_createInterval <= 0.0f)
	{
		Create();
		m_createInterval = MyMath::Random(60.0f, 180.0f);
	}
}

void PartsCreater::Create()
{
	auto points = GetFactoryPoints(m_world->GetGameManager().GetFactoryManager().All());
	MyVector3 position;
	Point2 point;
	//�����ʒu��ݒ�  �O��̈ʒu�Ƌ߂������ꍇ���ړ��s�̈ʒu�ɐ������ꂽ�ꍇ,�ă����_��
	do
	{
		position = MyMath::Random(MinCreatePosition, MaxCreatePosition);
		point = PathFind3DUtility::ToNodePoint2(position);
	} while (MyVector3::Distance(position, m_prevCreatePosition) <= 20.0f || m_world->GetFieldMap()[point] != 0 || VectorUtility::IsExistence<Point2>(points, point));

	//����
	m_world->GetGameManager().AddParts(std::make_shared<Parts>(*m_world, position));
	m_prevCreatePosition = position;
}

std::vector<Point2> PartsCreater::GetFactoryPoints(const FactoryPtr & factory) const
{
	//�����̎���Ǝ����̈ʒu��z��Ɍ������ĕԂ�
	std::vector<Point2> result;

	auto circlePoints = factory->GetPoints();
	auto myPoints = factory->MyPoints();

	std::copy(circlePoints.begin(), circlePoints.end(), std::back_inserter(result));
	std::copy(myPoints.begin(), myPoints.end(), std::back_inserter(result));

	return result;
}

std::vector<Point2> PartsCreater::GetFactoryPoints(const FactoryPtrs & factorys) const
{
	std::vector<Point2> result;
	//����񂵂Ĕz��Ɍ���
	for (auto factory : factorys)
	{
		auto points = GetFactoryPoints(factory);
		std::copy(points.begin(), points.end(), std::back_inserter(result));
	}

	return result;
}
