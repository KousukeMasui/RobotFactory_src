#include "PlayerOrderState.h"
#include"../../Player.h"
#include"Input/Mouse/Mouse.h"
#include"../PlayerStateID.h"
#include"Manager/GameManager.h"
#include"Math/Collision/Collision3D.h"
#include"Actor/Unit/Base/UnitMessageID.h"
#include"Actor/UnitFactory/UnitFactory.h"
#include"Base/VectorUtility/VectorUtility.h"
PlayerOrderState::PlayerOrderState(IWorld& world,Player * player, UnitPtr * unit):
	m_world(world),
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
		FactoryPtr factory = m_player->GetMouseSelect().HitFactory();
		if (factory != nullptr)
		{
			auto removes = m_world.GetGameManager().GetMetaAI().GetUnitPoints(**m_unit);
			auto targets = VectorUtility::NonObjects<Point2>(factory->GetPoints(), removes);
			m_unit->get()->Agent().StartFind(targets, removes, false);
		}
		else
			m_unit->get()->Agent().StartFind(m_player->GetMouseSelect().GetCursor().Position());
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
