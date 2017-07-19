#include "GamePlayAutoState.h"
#include"UI/Sprite/Sprite.h"
#include"Input/Mouse/Mouse.h"
#include"../GamePlayStateID.h"
#include"World/World.h"
#include"Actor/UnitFactory/UnitFactory.h"
#include"UI/Font/FontSprite.h"
#include"UI/UIAction/Move/Move.h"
#include"UI/UIAction/Link/Link.h"
#include"Screen/Screen.h"
GamePlayAutoState::GamePlayAutoState(IWorld& world):
	m_world(world),
	m_mouseSelect(world)
{
	m_manager.AddSprite(0, std::make_shared<Sprite>(TEXTURE_ID::BACK, MyVector2(30, 30), MyVector2(1, 1), MyVector2(0, 0)));
	//�����`��
	auto fontSprite = std::make_shared<FontSprite>(Font_ID::JAPANISE_FONT, 
		MyVector2((float)Screen::SCREEN_SIZE.x, ((float)Screen::SCREEN_SIZE.y - 210)), "���j�b�g��I�����ĉ�����", Color::Black);
	fontSprite->SetAction(std::make_shared<Link>(1, true, std::make_shared<Move>(MyVector2((float)Screen::SCREEN_SIZE.x, ((float)Screen::SCREEN_SIZE.y - 210)), MyVector2(-800.0f, ((float)Screen::SCREEN_SIZE.y - 210)), 600.0f)));
	m_manager.AddText(1, fontSprite);
	m_worldSpriteManager.Set(TEXTURE_ID::AUTO);
}

GamePlayAutoState::~GamePlayAutoState()
{
}

void GamePlayAutoState::Initialize()
{
	//�J���������L����
	m_world.GetCamera()->Controll(true);
}

void GamePlayAutoState::Update(float deltaTime)
{
	//�J�����̍X�V����
	m_world.GetCamera()->Update(deltaTime);
	//�}�E�X�J�[�\�������j�b�g�ɐG��Ă�����擾
	auto unit = m_mouseSelect.Update(deltaTime);
	//���N���b�N���ꂽ��
	if (Mouse::GetInstance().IsPressUp(MouseCommand::LEFT))
	{
		//���j�b�g���H���
		m_world.GetCommandFactory()->SelectUnit(unit);
	}
	//UI�f�[�^���X�V
	m_worldSpriteManager.Clear();
	auto units = m_world.GetCommandFactory()->GetAutoUnits();
	for (auto u : units)
	{
		m_worldSpriteManager.Save(TEXTURE_ID::AUTO, u->Position() + MyVector3(0, 40, 0), MyVector2(20, 20));
	}
	m_manager.Update(deltaTime);
}

void GamePlayAutoState::Draw() const
{
	m_manager.Draw();
	m_mouseSelect.Draw();
	m_worldSpriteManager.Draw();
}

void GamePlayAutoState::End()
{
	m_worldSpriteManager.Clear();
}

int GamePlayAutoState::Next() const
{
	return (int)GamePlayStateID::COMMAND;
}

bool GamePlayAutoState::IsEnd() const
{
	return Mouse::GetInstance().IsPressUp(MouseCommand::LEFT) && 
		m_manager.FindSprite(0)->IsCollide(Mouse::GetInstance().Position());
}
