#include "Unit.h"
#include"Actor\Base\IWorld.h"
#include"Actor\Base\ActorGroup.h"
#include"AITree\Idle\IdleNode.h"
#include"Math\Collision\Collision3D.h"
#include"Math\Collision\Model\ModelCollision.h"
#include"Loader\Loader.h"
#include"Math/MyRect/MyRect.h"
#include"Manager\GameManager.h"
#include"Base/RoadFinder/PathFind3DUtility.h"
#include"Base/RoadFinder/Map/FieldMap.h"
#include"Base\RoadFinder\PathFinder.h"
#include"Effect\Effect3D.h"
#include"World/World.h"
#include"Base/VectorUtility/VectorUtility.h"
#include"Math/Shapes/Renderer/ShapeRenderer.h"
#include"Base/UnitMessageID.h"
#include"Base/UnitAnimationID.h"
#include"Actor/UnitFactory/UnitFactory.h"
Unit::Unit(IWorld & world, InfluenceID influence, const MyVector3& position, const UnitStatus& status) :
	LiftObject(LIFT_ID::UNIT, position),
	m_world(world),
	m_isDelete(false),
	m_model(MODEL_ID::UNIT, false, UnitAnimationID::IDLE, true, GetPose()),
	m_sphere(m_position, 10.0f),
	m_capsule(m_position, 20.0f, 10.0f),
	m_nodeID(-1),
	m_status(status)
{
	m_influence = influence;
	m_model.Update(0.0f, GetPose());
	m_AITree.SetRoot(std::make_shared<IdleNode>(m_world, *this));
	//モデルの色の設定
	COLOR_F color;
	if (m_influence == InfluenceID::ENEMY)
	{
		color.r = 51.0f;
		color.b = 0.0f;
	}
	else
	{
		color.r = 0.0f;
		color.b = 51.0f;
	}
	color.g = 0.0f;
	color.a = 1.0f;
	const int index[] = { 0,5,6,8,9,11 };
	auto ambColor = color;
	ambColor.r *= 0.5f;
	ambColor.b *= 0.5f;
	for (int i = 0; i < 6; i++)
	{
		MV1SetMaterialDifColor(m_model.GetModelID(), index[i], color);
		
		MV1SetMaterialAmbColor(m_model.GetModelID(), index[i], ambColor);
	}

	//m_status.hp /= 2.0f;
}
Unit::~Unit()
{
	m_model.Delete();
}
void Unit::CreateAI(const std::function<void()>& createFunc)
{
	Point2 my = PathFind3DUtility::ToNodePoint2(m_position);
	//X軸に、かつ真ん中の方向に出現させる
	auto fieldMap = m_world.GetFieldMap();
	//真ん中のX
	int centerX = fieldMap.width() / 2;
	int X = -1;//どの方向に進むか 1 or -1
	//真ん中より左の場合
	if ((centerX - my.x) > 0)
	{
		X = 1;
	}

	PathFinder finder(fieldMap);
	Point2 point(0,0);
	NodePtr node = nullptr;
	do
	{
		point.x += X;
		node = finder[my + point];
	} while (node->Index() != 0);

	Message((int)UnitMessageID::ROOT, &PathFind3DUtility::ToPosition(node->position()));
	m_stopFunc = createFunc;
}

UnitStatus& Unit::GetStatus()
{
	return m_status;
}

bool Unit::IsCollide(const Line3D & line)
{
	return Collision3D::Capsule_Capsule(m_capsule.m_line.m_start, m_capsule.m_line.m_end, m_capsule.m_radius, line.m_start,line.m_end, 0.0f);
}
bool Unit::IsDelete() const
{
	return m_isDelete;
}

bool Unit::IsDead() const
{
	return m_status.hp <= FLT_EPSILON;
}

void Unit::Heal(float value)
{
	float prevHP = m_status.hp;
	//上限を超えないようにhpを増加
	m_status.hp = std::fminf(m_status.hp + value, (float)m_status.maxHP);
	float healPower = m_status.hp - prevHP;//回復量
	//回復処理が行われていない場合 エフェクトを生成しない
	if (healPower <= FLT_EPSILON * 2) return;
	//エフェクト再生
	auto effect = m_world.CreateEffect(EffectID::HEAL);
	effect->SetPositionFunc([&]() {return Position(); });
	effect->SetScale(MyVector3(10, 10, 10));
	//回復量をUI表示
	//スクリーン座標に変換
	//VECTOR screenUnitPos = ConvWorldPosToScreenPos(Converter::MyVector3ToVECTOR(m_position));
}

void Unit::RootMessage(int messageID, void * data)
{
	if (m_stopFunc != nullptr) {
		m_stopFunc(); m_stopFunc = nullptr;
	}
	std::vector<MyVector3> root;
	switch (messageID)
	{
	case (int)UnitMessageID::ROOT:
		root.push_back(*(MyVector3*)data);
		break;
	case (int)UnitMessageID::ROOT_VECTOR:
		for (auto point : (*(std::vector<Point2>*)data))
			root.push_back(PathFind3DUtility::ToPosition(point));
		break;
	}
	m_roadPositions = root;
}

void Unit::LiftDown(FactoryPtr factory)
{
	//現在のステータスを取得
	auto status = m_status;
	status.hp = 0.1f;
	//自分は削除される
	m_isDelete = true;

	factory->Create(status);
}

int Unit::NodeID() const
{
	return m_nodeID;
}

bool Unit::IsCollide(const Unit & other)
{
	return m_sphere.IsCollide(other.GetSphere());
}

void Unit::Collide(Unit& other)
{
	//どちらかが移動していない場合
	if (!IsMove())
	{
		//もう片方を移動させて終了
		other.Move(-other.GetVelocity() * other.GetStatus().MoveSpeed());
		other.RoadDelete();
		return;
	}
	else if (!other.IsMove()) {
		Move(-GetVelocity() * GetStatus().MoveSpeed());
		RoadDelete();
		return;
	}
	//互いに押し出す場合
	float y = m_position.y;
	//現在の距離
	float distance = MyVector3::Distance(GetSphere().m_center, other.GetSphere().m_center);
	//押しだす長さ
	float length = GetSphere().m_radius + other.GetSphere().m_radius - distance;
	//押し出す向き
	MyVector3 velocity = MyVector3::Normalize(GetSphere().m_center - other.GetSphere().m_center);
	float myLength = MyVector3::Length(m_velocity * GetStatus().MoveSpeed());
	float otherLength = MyVector3::Length(other.GetVelocity() * other.GetStatus().MoveSpeed());
	float total = myLength + otherLength;
	//互いに移動していない場合早期リターン
	if (total <= FLT_EPSILON) return;
	//それぞれの移動量に応じて押し出し
	float persec = myLength / (myLength + otherLength);
	Move(velocity * length * persec);
	Move(MyVector3(m_position.x, y, m_position.z) - m_position);

	y = other.Position().y;
	other.Move(-velocity * length * persec);
	other.Move(MyVector3(other.Position().x, y, other.Position().z) - other.Position());

	//違う勢力の場合
	if (other.GetInfluence() != m_influence)
	{
		//移動方向に相手がいる場合
		if (Converter::RadToDeg(MyVector3::Angle(other.GetVelocity(), GetVelocity())) > 90.0f)
		{
			//移動を終了
			RoadDelete();
			other.RoadDelete();
		}
	}
}

Sphere Unit::GetSphere() const
{
	return m_sphere;
}
void Unit::RoadDelete()
{
	m_roadPositions.clear();
}

void Unit::Update(float deltaTime)
{
	SetVelocity();//移動方向を設定
	m_AITree.Update(deltaTime);
	m_nodeID = m_AITree.ID();
	//モデル更新処理 速度に応じてアニメーションを早める
	m_model.Update(deltaTime + 0.1f * GetStatus().speed, GetPose());

	//ステージ外に出れないようにする
	float distance = MyVector3::Distance(MyVector3(800, 0, 800), m_position);
	if (distance >= 800)
	{
		MyVector3 vec = (MyVector3(800, 0, 800) - m_position).Normalize();
		float length = distance - 800;
		Move(vec *length);
		RoadDelete();
	}
}

void Unit::Move(const MyVector3 & velocity)
{
	m_capsule.Translate(velocity);
	m_position += velocity;
	m_sphere.m_center = m_position;
}

Unit& Unit::GetParam()
{
	return *this;
}

bool Unit::IsMove() const
{
	return !m_roadPositions.empty();
}

LiftObject* Unit::GetLift()
{
	return &*m_liftObject;
}

MyVector3 Unit::GetVelocity() const
{
	return m_velocity;
}

AnimationModel& Unit::GetModel()
{
	return m_model;
}

bool Unit::LerpToVelocity(const MyVector3& velocity)
{
	//移動しない場合回転を行わない
	if (velocity.Length() <= FLT_EPSILON) return true;
	//velocity方向に回転させる
	m_rotate = MyMatrix4::Lerp(m_rotate, MyMatrix4::SetForward(-velocity, MyVector3(0, 1, 0)),0.1f);
	return Converter::RadToDeg(MyVector3::Angle(velocity, -m_rotate.GetForward())) <= 1.0f;
}

MyVector3 Unit::ToNextVelocity() const
{
	if (m_roadPositions.empty()) return MyVector3::Zero();

	return m_roadPositions.back() - m_position;
}

MyVector3 Unit::Target() const
{
	return m_roadPositions.front();
}

void Unit::SetVelocity()
{
	MyVector3 velocity;
	do {
		//経路がない場合false
		if (m_roadPositions.empty())
		{
			m_velocity = MyVector3::Zero();
			return;
		}
		//移動方向を求める
		velocity = ToNextVelocity();

		//距離が一定以下の場合、再度計算させる
		if (velocity.Length() <= m_status.MoveSpeed())
		{
			m_roadPositions.pop_back();
		}
		else break;
	} while (true);

	//移動方向を変数に入れる
	m_velocity = velocity.Normalize();
}

void Unit::Draw() const
{
	m_model.Draw();

	//for (auto center : m_roadPositions)
	//{
	//	DrawCube3D(Converter::MyVector3ToVECTOR(center - MyVector3(PathFind3DUtility::size.x / 2.0f, 16.0f, PathFind3DUtility::size.y / 2.0f)),
	//		Converter::MyVector3ToVECTOR(center + MyVector3(PathFind3DUtility::size.x / 2.0f, 16.0f, PathFind3DUtility::size.y / 2.0f)),
	//		GetColor(255, 0, 0), GetColor(255, 0, 0), false);
	//}
}

InfluenceID Unit::GetInfluence() const
{
	return m_influence;
}

void Unit::Message(int messageID, void * data)
{
	if (messageID == (int)UnitMessageID::ROOT || messageID == (int)UnitMessageID::ROOT_VECTOR)
	{
		RootMessage(messageID, data);
		return;
	}
	switch (messageID)
	{
	case (int)UnitMessageID::HEAL:
		Heal(*(float*)data);
		break;
	case (int)UnitMessageID::DAMAGE:
		GetStatus().hp -= *(int*)data;
		break;
	case (int)UnitMessageID::LIFT:
		if (data == nullptr)
			m_liftObject = nullptr;
		else m_liftObject = *(LiftObjectPtr*)data;
		break;
	default:
		break;
	}
}