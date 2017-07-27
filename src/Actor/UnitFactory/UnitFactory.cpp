#include "UnitFactory.h"
#include"Actor\Base\IWorld.h"
#include"Manager\GameManager.h"
#include"Actor\Unit\Unit.h"
#include"Base/RoadFinder/PathFind3DUtility.h"
#include"Base\RoadFinder\Map\FieldMap.h"
#include"Math/Collision/Model/ModelCollision.h"
#include"Effect\Effect3D.h"
#include"Base/VectorUtility/VectorUtility.h"
#include"Math/Converter.h"
#include"Actor/Unit/AITree/Node/UnitNodeID.h"
#include"Math/Collision/Collision3D.h"
#include"Math/Shapes/Renderer/ShapeRenderer.h"
#include"Math/Extrusion/Extrusion3D.h"
#include"Actor/Unit/Base/UnitMessageID.h"
const MyVector3 EFFECT_SCALE = MyVector3(60, 40, 60);

UnitFactory::UnitFactory(IWorld& world, InfluenceID influence, const MyVector3& position, FactoryManager& manager):
	m_world(world),
	m_manager(manager),
	m_model(MODEL_ID::FACTORY,false, MyMatrix4::Scale(0.025f, 0.025f, 0.025f) * MyMatrix4::Translate(position) ),
	m_point(PathFind3DUtility::ToNodePoint2(position)),
	m_param(position,influence),
	m_status(world.GetGameManager().GetCSV(),[&](const UnitStatus& status) {CreateStart(status); }),
	m_autoAI(world,position,*this),
	m_heal(world,this)
{
	//周りのpointを計算
	PointsSet();
}
UnitFactory::~UnitFactory()
{
}

void UnitFactory::ChangeInfluence(InfluenceID influence)
{
	m_manager.Move(m_param.influence, influence, this);
	m_param.influence = influence;
	m_heal.ChangeColor(influence);
}

const FactoryHeal & UnitFactory::GetHeal() const
{
	return m_heal;
}

void UnitFactory::Update(float deltaTime)
{
	m_autoAI.Update(deltaTime);
	m_heal.Update(deltaTime);
}

void UnitFactory::Draw() const
{
	m_model.Draw();
	m_heal.Draw();
	m_autoAI.Draw();
}

//消えることがないのでfalseを返す
bool UnitFactory::IsDelete()
{
	return false;
}

FactoryParam & UnitFactory::GetParam()
{
	return m_param;
}
//周りのポイントにいるか確認
bool UnitFactory::IsCollide(const MyVector3& position)
{
	Point2 point = PathFind3DUtility::ToNodePoint2(position);

	return VectorUtility::IsExistence<Point2>(m_circlePoints,point)|| VectorUtility::IsExistence<Point2>(m_myPoints, point);
}

bool UnitFactory::IsCollide(const Sphere & other, HitInfo & hit) const
{
	hit = m_param.m_box.IsCollide(other);

	return hit.isHit;
}

bool UnitFactory::IsCollide(const Capsule & capsule) const
{
	return m_param.m_box.IsCollide(capsule).isHit;
}

HitInfo UnitFactory::IsCollide(const Line3D & line) const
{
	//当たり判定を行い、接触点を求める
	return m_param.m_box.IsCollide(line);
}

bool UnitFactory::IsCollide(const Unit & unit)
{
	return VectorUtility::IsExistence<Point2>(GetPoints(), PathFind3DUtility::ToNodePoint2(unit.Position()));
}

void UnitFactory::Collide(Unit & unit)
{
	//移動中でない場合
	if (!unit.Agent().IsMove()) return;

	//移動方向に工場がある場合
	if (m_param.m_box.IsCollide(Ray(unit.Position(), unit.Agent().ToNextVelocity())).isHit)
	{
		//移動速度より近い(次のフレームで追い越す)場合
		if (MyVector3::Distance(unit.Agent().EndPoint(), unit.Position()) <= unit.GetStatus().Status(UNIT_STATUS_ID::SPD) ||
			IsCollide(Sphere(unit.Agent().EndPoint(), 1.0f), HitInfo())//工場を目的地としていた場合
			)
		{
			//移動終了
			unit.Agent().Delete();
			return;
		}

		//エネミーの場合、経路探索で動いているので新しく経路を与えない
		if (unit.GetInfluence() != InfluenceID::PLAYER) return;
		//重なった場合などに毎フレーム呼び出されてしまうので
		Ray ray(unit.Position(), unit.Agent().ToNextVelocity());
		//次の目的地までの方向に工場がある場合
		if (m_param.m_box.IsCollide(ray).isHit)
		{
			//経路探索
			m_world.GetGameManager().GetMetaAI().GetFind().PathFind(
				m_world.GetGameManager().GetMetaAI().GetFind().CreatePathFinder(), unit.Agent().EndPoint(), unit.Agent());
		}

	}
}

void UnitFactory::PartsCount(int add)
{
	m_status.partsCount += add;
}

int UnitFactory::PartsCount() const
{
	return m_status.partsCount;
}

FactoryStatus & UnitFactory::Status()
{
	return m_status;
}

void UnitFactory::StatusUp(FactoryStatusID id)
{
	m_status.StatusUp(id, &m_world.GetGameManager());
	//回復関連の場合
	if (id == FactoryStatusID::HEAL_POWER || id == FactoryStatusID::HEAL_RANGE)
	{
		m_heal.StatusUp(m_status);
	}
}

void UnitFactory::CreateStart(const UnitStatus & status)
{
	
	m_createStatus.push_back(status);
	if (m_createStatus.size() >= 2) return;
	Create(m_createStatus.front());
}

void UnitFactory::Create(const UnitStatus & status)
{
	auto unit = std::make_shared<Unit>(m_world, m_param.influence, m_param.Position(), status);
	m_world.GetGameManager().AddUnit(InfluenceID::EFFECT, unit);
	//ユニットが停止したら生成関数をもう一度行う
	unit->CreateAI([&]() {
		if (!m_createStatus.empty())m_createStatus.pop_front();
		if (m_createStatus.size() <= 0) return;
		Create(m_createStatus.front());
	});
}

void UnitFactory::Damage(float attack, InfluenceID influence)
{
	m_status.hp -= attack;
	if (m_status.hp <= 0.0f)
	{
		ChangeInfluence(influence);
		m_status.hp = 1;
	}
}

std::vector<Point2> UnitFactory::GetPoints() const
{
	return m_circlePoints;
}

void UnitFactory::AddTarget(Point2 target)
{
	m_targetedPoints.push_back(target);
}

std::vector<Point2> UnitFactory::MyPoints() const
{
	return m_myPoints;
}

void UnitFactory::SelectUnit(const UnitPtr & unit)
{
	m_autoAI.Select(unit);
}

const UnitPtrs UnitFactory::GetAutoUnits() const
{
	return m_autoAI.GetUnits();
}

void UnitFactory::Heal(float power)
{
	if (m_status.hp < m_status.maxHP)
	{
		m_status.hp = std::fminf((m_status.hp + power), (float)m_status.maxHP);
		//工場に回復エフェクトを作る
		auto effect = m_world.CreateEffect(EffectID::HEAL);
		effect->SetPosition(m_param.Position());
		effect->SetScale(EFFECT_SCALE);
	}
}

void UnitFactory::PointsSet()
{
	int right = 0;
	int left = 0;
	int top = 0;
	int bottom = 0;
	PathFinder f = m_world.GetGameManager().GetMetaAI().GetFind().CreatePathFinder();
	//center　+x,0が0になるまで回す
	do
	{
		right++;
	} while (!f[m_point + Point2(right, 0)]->walkable());
	do
	{
		left--;
	} while (!f[m_point + Point2(left, 0)]->walkable());
	do
	{
		top--;
	} while (!f[m_point + Point2(0, top)]->walkable());
	do
	{
		bottom++;
	} while (!f[m_point + Point2(0, bottom)]->walkable());
	Point2 rightDown = Point2(m_point.x + right, m_point.y + bottom);
	Point2 leftUp = Point2(m_point.x + left, m_point.y + top);//
 //										調整
	int weight = rightDown.x - leftUp.x + 1;
	int height = rightDown.y - leftUp.y + 1;

	for (int i = 0; i < height; i++)
	{
		m_circlePoints.push_back(Point2(leftUp.x, leftUp.y + i));
		m_circlePoints.push_back(Point2(rightDown.x, leftUp.y + i));
	}

	for (int i = 1; i < weight; i++)
	{
		m_circlePoints.push_back(Point2(leftUp.x + i, leftUp.y));
		m_circlePoints.push_back(Point2(leftUp.x + i, rightDown.y));
	}

	for (int x = left + 1; x < right; x++)
	{
		for (int y = top + 1; y < bottom; y++)
		{
			m_myPoints.push_back(m_point + Point2(x, y));
		}
	}
}

void UnitFactory::NonInfluenceUpdate(float deltaTime)
{
	//PathFinder f(m_world.GetFieldMap());
	//自分の周りにユニットがいたらその所属になる
	m_world.GetGameManager().GetUnitManager().Function([&](const UnitPtr& unit) {
		if (unit->IsDead()) return;
		Point2 point = PathFind3DUtility::ToNodePoint2(unit->Position());
		
		if(VectorUtility::IsExistence<Point2>(GetPoints(), point))
		{
			ChangeInfluence(unit->GetInfluence());
		}
	});
}
