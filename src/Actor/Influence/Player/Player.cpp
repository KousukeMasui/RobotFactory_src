#include "Player.h"
#include"Input\Mouse\Mouse.h"
#include"Screen\Screen.h"
#include<DxLib.h>
#include"Actor/Base/IWorld.h"
#include"World/World.h"
#include"Base/RoadFinder/Map/FieldMap.h"
#include"Base/RoadFinder/PathFind3DUtility.h"
#include"Actor\UnitFactory\UnitFactory.h"
#include"UI/Sprite/Sprite.h"
#include"Math/Collision/Model/ModelCollision.h"
#include"Base/VectorUtility/VectorUtility.h"
#include"Actor/Unit/AITree/Node/UnitNodeID.h"
#include"State/Select/PlayerSelectState.h"
#include"State/Order/PlayerOrderState.h"
#include"State/PlayerStateID.h"
#include"Scene/GamePlay/GamePlaySpriteID.h"

const MyVector3 DEFAULT_CURSOR_SCALE = MyVector3(20, 1, 20);		//�����̃J�[�\���T�C�Y
const MyVector3 COL_FACTORY_CURSOR_SCALE = MyVector3(80, 1, 80);	//�H���I�����Ă���ۂ̃J�[�\���T�C�Y
Player::Player(IWorld & world):
	Influence(world,InfluenceID::PLAYER),
	m_model(MODEL_ID::CIRCLE),
	m_isAutoSelect(false),
	m_mouseSelect(world)
{
	m_stateManager.Add((int)PlayerStateID::SELECT, std::make_shared<PlayerSelectState>(world,this));
	m_stateManager.Add((int)PlayerStateID::ORDER, std::make_shared<PlayerOrderState>(world,this,&m_selectedUnit));
	m_stateManager.SetState((int)PlayerStateID::SELECT);
}

Player::~Player()
{
}

void Player::Update(float deltaTime)
{
	//�}�E�X�̐�̃��j�b�g���擾
	m_onMouseUnit = m_mouseSelect.Update(deltaTime);

	m_stateManager.Update(deltaTime);

	CursorEffect();
	//�}�E�X�̈ʒu�̃��j�b�g�̃X�e�[�^�X�`���Sprite��ǉ�
	OnMouseUnitStatusDraw();
}

void Player::Draw() const
{
	SelectUnitDraw();//�I�����j�b�g�ɃJ�[�\���`��
	m_mouseSelect.Draw();//�J�[�\���`��
}
void Player::Select(const UnitPtr & unit)
{
	m_selectedUnit = m_onMouseUnit;
	//���ߑ҂��ɂ���
	m_selectedUnit->RoadDelete();
}
SelectCursor & Player::GetCursor()
{
	return m_mouseSelect.GetCursor();
}

void Player::OnMouseUnitStatusDraw()
{
	//�Q�[�W�摜������
	m_world.GetUIManager().DeleteSprite((int)GamePlaySpriteID::PLAY_GAUGE);
	//�}�E�X�����j�b�g�̈ʒu�ɂȂ��ꍇ
	if (m_onMouseUnit == nullptr)
	{
		return;//�������^�[��
	}

	//�J��Ԃ����A�֐��ɂ���܂ł��Ȃ��̂Ń����_�����
	auto gaugeDraw = [&](int num, MyVector2 startPosition)
	{
		for (int i = 0; i < num; i++)
		{
			auto gaugeSprite = std::make_shared<Sprite>(TEXTURE_ID::COMMAND_GAUGE, startPosition + 15.0f * i, MyVector2(1.0f, 1.0f), MyVector2(0.5f, 0.5f));
			m_world.GetUIManager().AddSprite((int)GamePlaySpriteID::PLAY_GAUGE, gaugeSprite);
		}
	};

	//HP�̕`��
	gaugeDraw(m_onMouseUnit->GetStatus().factoryMaxHP, MyVector2(135,Screen::SCREEN_SIZE.y - 150.0f));
	//�U���͂̕`��
	gaugeDraw(m_onMouseUnit->GetStatus().attack, MyVector2(135, Screen::SCREEN_SIZE.y - 100.0f));
	//���x�̕`��
	gaugeDraw(m_onMouseUnit->GetStatus().speed, MyVector2(135, Screen::SCREEN_SIZE.y - 50.0f));
}

void Player::SelectUnitDraw() const
{
	if (m_selectedUnit == nullptr) return;
	auto position = m_selectedUnit->Position() + MyVector3(0, 2, 0);
	//�͈͂̃��f���̐F��ς���
	m_model.SetMaterialColor(0, Color(0.0f, 0.0f, 1.0f, 1.0f));

	m_model.Draw(position, MyVector3(13, 1, 13), 0.0f);
}

void Player::CursorEffect()
{
	//�J�[�\���̑傫���������T�C�Y�ɂ���
	m_mouseSelect.GetCursor().Scale(DEFAULT_CURSOR_SCALE);
	if (m_onMouseUnit != nullptr)
	{
		m_mouseSelect.GetCursor().Position(m_onMouseUnit->Position());
		return;
	}

	auto factorys = m_world.GetGameManager().GetFactoryManager().All();
	for (auto factory : factorys)
	{
		if (factory->GetParam().m_box.IsCollide(Sphere(m_mouseSelect.GetCursor().Position(), 1.0f)).isHit)
		{
			m_mouseSelect.GetCursor().Position(factory->GetParam().Position());
			m_mouseSelect.GetCursor().Scale(COL_FACTORY_CURSOR_SCALE);
			break;
		}
	}
}
