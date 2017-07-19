#include "PlayerSelectState.h"
#include"Input/Mouse/Mouse.h"
#include"Actor/Unit/Unit.h"
#include"Actor/Unit/AITree/Node/UnitNodeID.h"
#include"Actor/Influence/Player/Player.h"

#include"../PlayerStateID.h"
#include"Manager/GameManager.h"
#include"World/World.h"
PlayerSelectState::PlayerSelectState(IWorld& world,Player* player):
	m_world(world),
	m_player(player),
	m_isEnd(false)
{
}

PlayerSelectState::~PlayerSelectState()
{
}

void PlayerSelectState::Initialize()
{
	m_isEnd = false;
}

void PlayerSelectState::Update(float deltaTime)
{
	if (Mouse::GetInstance().IsPressUp(MouseCommand::LEFT))
	{
		auto unit = m_player->GetCursor().IsCollide(m_world.GetGameManager().GetUnitManager().GetVector(InfluenceID::PLAYER));
		if (unit != nullptr)
		{
			m_player->Select(unit);
			m_isEnd = true;
			return;
		}
		//ユニットをクリックしていない時
		auto factory = m_player->GetCursor().IsCollide(m_world.GetGameManager().GetFactoryManager().GetVector(InfluenceID::PLAYER));
		if (factory != nullptr)
		{
			//シーンのステートを進める コマンドを開く
			m_world.Command(factory);
		}
	}
}

void PlayerSelectState::Draw() const
{
}

void PlayerSelectState::End()
{
}

int PlayerSelectState::Next() const
{
	return (int)PlayerStateID::ORDER;
}

bool PlayerSelectState::IsEnd() const
{
	return m_isEnd;
}
