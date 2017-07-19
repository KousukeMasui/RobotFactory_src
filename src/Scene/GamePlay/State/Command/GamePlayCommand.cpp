#include "GamePlayCommand.h"
#include"UI/FactoryUI/FactoryUI.h"
#include"World/World.h"
GamePlayCommand::GamePlayCommand(World & world):
	m_world(world),
	m_factoryUI(std::make_shared<FactoryUI>(world)),
	m_nextID(GamePlayStateID::COMMAND),
	m_isEnd(false)
{
}

GamePlayCommand::~GamePlayCommand()
{
}

void GamePlayCommand::Initialize()
{
	m_isEnd = false;
	m_factoryUI->Create(m_world.GetCommandFactory());
	m_world.GetCamera()->Controll(false);
}

void GamePlayCommand::Update(float deltaTime)
{
	m_factoryUI->Update(deltaTime);
	if (!m_world.IsCommand())
	{
		m_isEnd = true;
		m_nextID = GamePlayStateID::PLAY;
	}
	else if (m_factoryUI->IsAuto())
	{
		m_isEnd = true;
		m_nextID = GamePlayStateID::AUTO_SELECT;
	}
}

void GamePlayCommand::Draw() const
{
	m_factoryUI->Draw();
}

void GamePlayCommand::End()
{
	m_factoryUI->Delete();
}

int GamePlayCommand::Next() const
{
	return (int)m_nextID;
}

bool GamePlayCommand::IsEnd() const
{
	return m_isEnd;
}
