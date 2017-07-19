#include "PlayerOrderState.h"
#include"../../Player.h"
#include"Input/Mouse/Mouse.h"
#include"../PlayerStateID.h"
#include"Manager/GameManager.h"
#include"Math/Collision/Collision3D.h"
#include"Actor/Unit/Base/UnitMessageID.h"
#include"Actor/UnitFactory/UnitFactory.h"
PlayerOrderState::PlayerOrderState(IWorld& world,Player * player, UnitPtr * unit):
	m_player(player),
	m_unit(unit),
	m_isEnd(false)
{
	m_factorys = world.GetGameManager().GetFactoryManager().All();
}

PlayerOrderState::~PlayerOrderState()
{
}

void PlayerOrderState::Initialize()
{
	m_isEnd = false;
}

void PlayerOrderState::Update(float deltaTime)
{
	if (m_unit->get()->GetParam().IsDead())//ユニットが死亡したら
	{
		m_isEnd = true;
		*m_unit = nullptr;
		return;
	}
	m_isEnd = Mouse::GetInstance().IsPressUp(MouseCommand::LEFT);
}

void PlayerOrderState::Draw() const
{
}

void PlayerOrderState::End()
{
	//クリックした先に移動命令
	if (m_unit->get() != nullptr) {
		m_unit->get()->Message((int)UnitMessageID::ROOT, m_player->GetCursor().PositionPtr());
		OrderClickFactory();
	}
	//選択解除
	*m_unit = nullptr;
}

int PlayerOrderState::Next() const
{
	return (int)PlayerStateID::SELECT;
}

bool PlayerOrderState::IsEnd() const
{
	return m_isEnd;
}

void PlayerOrderState::OrderClickFactory()
{
	auto factory = m_player->GetCursor().IsCollide(m_factorys);
	if (factory == nullptr) return;
	//当たり判定を行い、接触点を求める
	//ここでunitがnullになってエラー
	auto hit = factory->GetParam().m_box.IsCollideRotate(Line3D(m_unit->get()->Position(), m_player->GetCursor().Position()));
	//工場と触れている場合 工場に接した場所で停止するように目的地を変更
	if (!hit.isHit) return;
	MyVector3 velocity = hit.hitPosition - m_unit->get()->Position();
	velocity.y = 0.0f;//高さは無効
	if (velocity.Length() <= m_unit->get()->GetSphere().m_radius / 2.0f)
	{
		m_unit->get()->RoadDelete();
		return;
	}
	m_unit->get()->Message((int)UnitMessageID::ROOT, &(hit.hitPosition + hit.normal * m_unit->get()->GetSphere().m_radius));
}

