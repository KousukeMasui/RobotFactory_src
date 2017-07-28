#include "Unit.h"
#include"Actor\Base\IWorld.h"
#include"Math/MyMath.h"
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

const MyVector3 STAGE_CENTER = MyVector3(800.0f, 0.0f, 800.0f);
Unit::Unit(IWorld & world, RootFind& find, InfluenceID influence, const MyVector3& position, const UnitStatus& status) :
	LiftObject(LIFT_ID::UNIT, position),
	m_world(world),
	m_isDelete(false),
	m_model(MODEL_ID::UNIT, false, UnitAnimationID::IDLE, true, GetPose()),
	m_capsule(m_position, world.GetGameManager().GetCSV().Get_F(CSV_DATA_ID::UNIT_HEIGHT, 1),
		world.GetGameManager().GetCSV().Get_F(CSV_DATA_ID::UNIT_RADIUS, 1)),
	m_nodeID(-1),
	m_status(status),
	m_influence(influence),
	m_toUnit(world.GetGameManager(),*this),
	m_rootAgent(find,*this)
{
	m_model.Update(0.0f, GetPose());
	m_AITree.SetRoot(std::make_shared<IdleNode>(m_world, *this));
	//色を変更するマテリアル番号
	auto changeMatIndices = m_world.GetGameManager().GetCSV().Gets_I(CSV_DATA_ID::UNIT_COLOR_CHANGE_INDICES);
	//色のパラメータを配列で取得
	std::vector<float> color, ambientColor;
	if (influence == InfluenceID::PLAYER) {
		color = m_world.GetGameManager().GetCSV().Gets_F(CSV_DATA_ID::PLAYER_COLOR);
		ambientColor = m_world.GetGameManager().GetCSV().Gets_F(CSV_DATA_ID::PLAYER_AMBIENT_COLOR);
	}
	else {
		color = m_world.GetGameManager().GetCSV().Gets_F(CSV_DATA_ID::ENEMY_COLOR);
		ambientColor = m_world.GetGameManager().GetCSV().Gets_F(CSV_DATA_ID::ENEMY_AMBIENT_COLOR);
	}
	//色を設定
	for (auto index : changeMatIndices) {
		Color c(color[0], color[1], color[2], color[3]);
		Color ambC(ambientColor[0], ambientColor[1], ambientColor[2], ambientColor[3]);
		m_model.SetMaterialColor(index, c);
		m_model.SetAmbientColor(index, ambC);
	}
}
Unit::~Unit()
{
	m_model.Delete();
}
void Unit::CreateAI(const std::function<void()>& createFunc)
{
	Point2 my = PathFind3DUtility::ToNodePoint2(m_position);
	float x = MyMath::Clamp(m_position.x - STAGE_CENTER.x, -1, 1);
	PathFinder finder = m_world.GetGameManager().GetMetaAI().GetFind().CreatePathFinder();
	Point2 point(0,0);
	NodePtr node = nullptr;
	do
	{
		point.x += (int)x;
		node = finder[my + point];
	} while (node->Index() != 0);

	m_rootAgent.SetRoot(PathFind3DUtility::ToPosition(node->position()));
	m_stopFunc = createFunc;
}

UnitStatus& Unit::GetStatus()
{
	return m_status;
}

bool Unit::IsCollide(const Line3D & line)
{
	return Collision3D::Capsule_Capsule(m_capsule.m_line.m_start, m_capsule.m_line.m_end,
		m_capsule.m_radius, line.m_start,line.m_end, 0.0f);
}
bool Unit::IsDelete() const
{
	return m_isDelete;
}

bool Unit::IsDead() const
{
	return m_status.Status(UNIT_STATUS_ID::HP) <= FLT_EPSILON;
}

void Unit::Heal(float value)
{
	float prevHP = m_status.Status(UNIT_STATUS_ID::HP);
	m_status.AddHP(value);
	//回復処理が行われていない場合 エフェクトを生成しない
	if ((m_status.Status(UNIT_STATUS_ID::HP) - prevHP) <= FLT_EPSILON * 2) return;
	//エフェクト再生
	auto effect = m_world.CreateEffect(EffectID::HEAL, Position(),MyVector3(10,10,10));
	effect->SetPositionFunc([&]() {return Position(); });
}
void Unit::LiftDown(FactoryPtr factory)
{
	//maxの10%のhpで復活
	m_status.AddHP((m_status.Status(UNIT_STATUS_ID::MAX_HP)/10) - m_status.Status(UNIT_STATUS_ID::HP));
	//自分は削除される
	m_isDelete = true;

	factory->Create(m_status);
}

int Unit::NodeID() const
{
	return m_nodeID;
}

bool Unit::IsCollide(const Unit & other)
{
	return Sphere(m_position, m_capsule.m_radius).IsCollide(other.GetSphere());
}

void Unit::Collide(Unit& other)
{
	//どちらかが移動していない場合
	if (!m_rootAgent.IsMove())
	{
		//もう片方を移動させて終了
		other.Move(-other.Agent().ToNextVelocity() * other.GetStatus().Status(UNIT_STATUS_ID::SPD));
		other.Agent().Delete();
		return;
	}
	else if (!other.Agent().IsMove()) {
		Move(-m_rootAgent.ToNextVelocity() * GetStatus().Status(UNIT_STATUS_ID::SPD));
		Agent().Delete();
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
	float myLength = MyVector3::Length(m_rootAgent.ToNextVelocity() * GetStatus().Status(UNIT_STATUS_ID::SPD));
	float otherLength = MyVector3::Length(other.Agent().ToNextVelocity() * other.GetStatus().Status(UNIT_STATUS_ID::SPD));
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
		if (Converter::RadToDeg(MyVector3::Angle(other.Agent().ToNextVelocity(), m_rootAgent.ToNextVelocity())) > 90.0f)
		{
			//移動を終了
			Agent().Delete();
			other.Agent().Delete();
		}
	}
}

Sphere Unit::GetSphere() const
{
	return Sphere(m_position, m_capsule.m_radius);
}

void Unit::Update(float deltaTime)
{
	m_rootAgent.Update(deltaTime, m_status.Status(UNIT_STATUS_ID::SPD));

	m_AITree.Update(deltaTime);
	m_nodeID = m_AITree.ID();
	//モデル更新処理 速度に応じてアニメーションを早める
	m_model.Update(deltaTime * GetStatus().Status(UNIT_STATUS_ID::SPD), GetPose());

	m_toUnit.Update();

	//ステージ外に出れないようにする
	float distance = MyVector3::Distance(STAGE_CENTER, m_position);
	if (distance >= 800)
	{
		MyVector3 vec = (STAGE_CENTER - m_position).Normalize();
		float length = distance - 800;
		Move(vec *length);
		Agent().Delete();
	}
}

void Unit::Move(const MyVector3 & velocity)
{
	if (m_stopFunc != nullptr) {
		m_stopFunc();
		m_stopFunc = nullptr;
	}
	m_capsule.Translate(velocity);
	m_position += velocity;
}

Unit& Unit::GetParam()
{
	return *this;
}

LiftObject* Unit::GetLift()
{
	return &*m_liftObject;
}

AnimationModel& Unit::GetModel()
{
	return m_model;
}

RootAgent & Unit::Agent()
{
	return m_rootAgent;
}

bool Unit::RotateVelocity(const MyVector3& velocity, float deltaTime)
{
	return SlerpRotate(velocity,deltaTime);
}

void Unit::Draw() const
{
	m_model.Draw();

	m_rootAgent.Draw(m_model.GetMaterialColor(0));
}

InfluenceID Unit::GetInfluence() const
{
	return m_influence;
}

void Unit::Message(int messageID, void * data)
{
	switch (messageID)
	{
	case (int)UnitMessageID::HEAL:
		Heal(*(float*)data);
		break;
	case (int)UnitMessageID::DAMAGE:
		GetStatus().AddHP(-*(float*)data);
		break;
	case (int)UnitMessageID::LIFT:
		if (data == nullptr)
			m_liftObject = nullptr;
		else m_liftObject = *(LiftObjectPtr*)data;
		break;
	case (int)UnitMessageID::TO_UNIT:
		m_toUnit.SetTarget(*(UnitPtr*)data);
		break;
	default:
		break;
	}
}