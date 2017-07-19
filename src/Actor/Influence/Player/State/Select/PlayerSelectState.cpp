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
		//���j�b�g���N���b�N���Ă��Ȃ���
		auto factory = m_player->GetCursor().IsCollide(m_world.GetGameManager().GetFactoryManager().GetVector(InfluenceID::PLAYER));
		if (factory != nullptr)
		{
			//�V�[���̃X�e�[�g��i�߂� �R�}���h���J��
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
