#include "UnitCreate.h"
#include"Actor/Unit/Base/Status/UnitStatus.h"
#include"World/World.h"
#include"../../Parameter/FactoryParam.h"
#include"Actor/Unit/Unit.h"
#include"Math/MyMath.h"
#include"Base/RoadFinder/PathFind3DUtility.h"
UnitCreate::UnitCreate(IWorld & world,RootFind& find, FactoryParam& param):
	m_world(world),
	m_param(param),
	m_find(find),
	m_sphere(param.Position(),30.0f)
{
	int x = (int)MyMath::Clamp(800.0f - m_param.Position().x, -1, 1);
	Point2 p = PathFind3DUtility::ToNodePoint2(param.Position());
	do {
		p.x += x;
	} while (!m_find.CreatePathFinder()[p]->walkable());
	m_sphere.m_center=PathFind3DUtility::ToPosition(p);
}
UnitCreate::~UnitCreate()
{
}
void UnitCreate::Update()
{
	if (m_createUnit != nullptr &&
		!m_createUnit->Agent().IsMove()) m_createUnit = nullptr;
	//�������郆�j�b�g�����Ȃ��ꍇ�I��
	if (m_status.empty()) return;

	Create();
}

bool UnitCreate::IsCollide()
{
	//�S�Ẵ��j�b�g���擾
	auto units = m_world.GetGameManager().GetUnitManager().All();
	//�ǂꂩ�ƏՓ˂�����true
	for (auto unit : units) {
		if (unit->GetSphere().IsCollide(m_sphere)) return true;
	}
	//�������Č��ݏo�����̃��j�b�g��������true
	return m_createUnit != nullptr;
}

void UnitCreate::Create(const UnitStatus & status)
{
	m_status.push_back(status);

	Create();
}

void UnitCreate::Create()
{
	//���j�b�g�ƏՓ˂��Ă���ꍇ�A�������Ȃ�
	if (IsCollide()) return;
	UnitStatus status = m_status.front();
	//����
	m_createUnit = std::make_shared<Unit>(m_world, m_find, m_param.influence, m_param.Position(), status);
	m_world.GetGameManager().AddUnit(InfluenceID::EFFECT, m_createUnit);
	//�ړ�����
	m_createUnit->Agent().SetRoot(m_sphere.m_center);
	//�������X�g����폜
	m_status.pop_front();
}
