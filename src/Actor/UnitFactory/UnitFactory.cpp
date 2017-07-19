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
	m_status([&](const UnitStatus& status) {CreateStart(status); }),
	m_autoAI(world,position,*this),
	m_heal(world,this)
{
	//周りのpointを計算
	PointsSet();
	//m_status.partsCount = 999;
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

	//当たり判定の描画
	//ShapeRenderer::Draw(m_param.m_box);
	/*for (auto point : m_circlePoints)
	{
		MyVector3 center = PathFind3DUtility::ToPosition(point);
		DrawCube3D(Converter::MyVector3ToVECTOR(center - MyVector3(PathFind3DUtility::size.x / 2.0f, 16.0f, PathFind3DUtility::size.y / 2.0f)),
			Converter::MyVector3ToVECTOR(center + MyVector3(PathFind3DUtility::size.x / 2.0f, 16.0f, PathFind3DUtility::size.y / 2.0f)),
			GetColor(255, 0, 0), GetColor(255, 0, 0), false);
	}*/
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

void UnitFactory::Collide(Unit & other, HitInfo & hit)
{

	//移動中でない場合
	if (!other.IsMove()) return;
	
	//移動方向に工場がある場合
	if (m_param.m_box.IsCollide(Ray(other.Position(), other.GetVelocity())).isHit)
	{
		//移動速度より近い(次のフレームで追い越す)場合
		if (MyVector3::Distance(other.Target(), other.Position()) <= other.GetStatus().MoveSpeed() ||
			IsCollide(Sphere(other.Target(), 1.0f), HitInfo())//工場を目的地としていた場合
			)
		{
			//移動終了
			other.RoadDelete();
			return;
		}

		Ray ray(other.Position(), other.ToNextVelocity());
		//次の目的地までの方向に工場がある場合
		if (m_param.m_box.IsCollide(ray).isHit)
		{
			//経路探索
			PathFinder f(m_world.GetFieldMap());
			other.Message((int)UnitMessageID::ROOT_VECTOR, &PathFind3DUtility::ToRoad(f.FindTarget(
				PathFind3DUtility::ToNodePoint2(other.Position(), f),
				PathFind3DUtility::ToNodePoint2(other.Target(), f)), f));
		}

	}
}

bool UnitFactory::IsCollide(const Unit & unit)
{
	return VectorUtility::IsExistence<Point2>(GetPoints(), PathFind3DUtility::ToNodePoint2(unit.Position()));
}

void UnitFactory::Collide(Unit & unit)
{
	//実際に衝突している場合 それ用の処理を行う
	//if (IsCollide(unit.GetSphere(), HitInfo()))
		Collide(unit, HitInfo());
	return;
	//これ以上工場に近づこうとしている場合、停止させる
	auto points = PathFind3DUtility::ToNodePoint2(Line3D(unit.Position(), unit.Position() + unit.ToNextVelocity() * 100.0f));
	for (auto p : points) {
		if (VectorUtility::IsExistence<Point2>(m_myPoints, p))
		{
			unit.RoadDelete();
			break;
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
	m_status.StatusUp(id);
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

void UnitFactory::Damage(int attack, InfluenceID influence)
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

	//center　+x,0が0になるまで回す
	do
	{
		right++;
	} while (m_world.GetFieldMap()[m_point + Point2(right, 0)] == 2);
	do
	{
		left--;
	} while (m_world.GetFieldMap()[m_point + Point2(left, 0)] == 2);
	do
	{
		top--;
	} while (m_world.GetFieldMap()[m_point + Point2(0, top)] == 2);
	do
	{
		bottom++;
	} while (m_world.GetFieldMap()[m_point + Point2(0, bottom)] == 2);
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
		Point2 point = PathFind3DUtility::ToNodePoint2(unit->Position());
		
		if(VectorUtility::IsExistence<Point2>(GetPoints(), point))
		//if(m_param.m_box.IsCollide(unit->GetSphere()).isHit)
		{
			ChangeInfluence(unit->GetInfluence());
		}
	});
}
