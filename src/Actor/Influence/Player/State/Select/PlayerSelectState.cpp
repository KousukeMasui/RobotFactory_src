#include "PlayerSelectState.h"
#include"Input/Mouse/Mouse.h"
#include"Actor/Unit/Unit.h"
#include"Actor/Unit/AITree/Node/UnitNodeID.h"
#include"Actor/Influence/Player/Player.h"

#include"../PlayerStateID.h"
#include"Manager/GameManager.h"
#include"World/World.h"
PlayerSelectState::PlayerSelectState(IWorld& world,Player* player,UnitPtr* unit):
	m_world(world),
	m_player(player),
	m_unit(unit),
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
		if (*m_unit != nullptr)
		{
			m_player->Select(*m_unit);
			m_isEnd = true;
			return;
		}
		
		//ユニットをクリックしていない時
		auto factory = m_player->GetMouseSelect().HitFactory();
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
