#include "Debug.h"
#include"Manager/GameManager.h"
#include"Actor\Camera\FollowCamera\FollowCamera.h"
#include"World/World.h"
#include"Base/VectorUtility/VectorUtility.h"
Debug::Debug(World & world, LerpCursor& cursor):
	m_world(world),
	m_isDebug(false),
	m_camera(std::make_shared<FollowCamera>()),
	m_unitTarget(MODEL_ID::CIRCLE),
	m_targetUnit(m_world.GetGameManager().GetUnitManager().GetVector(InfluenceID::ENEMY)[0]),
	m_target(CameraTarget::UNIT),
	m_cursor(cursor)
{
	m_camera->SetTarget([&]() {return m_targetUnit->Position(); });
	m_world.AddCamera(CameraMode::UNIT,m_camera);
}

Debug::~Debug()
{
}

bool Debug::IsDebug()
{
	return m_isDebug;
}

void Debug::Update(float deltaTime)
{
	ChangeDebug();//�f�o�b�O���[�h�ƒʏ탂�[�h�̐؂�ւ�
	//�J�����̃^�[�Q�b�g�̎�ނ�ύX
	CameraTargetChange();
	ChangeUnit();//�J�����̃��j�b�g��ύX
}

void Debug::Draw() const
{
	//printfDx("\n\n");
	//printfDx("���E�L�[�Ń��j�b�g�ƃJ�[�\���̕ύX\n");
	//printfDx("�㉺�L�[�Ń��j�b�g�ύX\n\n\n");
	//�ړ����̃I�u�W�F�N�g�̂ݖړI�n��`��
	if (m_targetUnit->IsMove())
	{
		//m_unitTarget.Draw(m_targetUnit->GetParam().roadPositions.front() + MyVector3(0, 2, 0), MyVector3(13, 1, 13), 0.0f);
	}
}

void Debug::Init()
{
	//�J���������j�b�g�Ǐ]�J�����ɕύX
	m_world.SetCamera(CameraMode::UNIT);
}

void Debug::End()
{
	//�J������ʏ�J�����ɕύX
	m_world.SetCamera(CameraMode::NORMAL);
}

void Debug::ChangeDebug()
{
	if (Input::GetInstance().IsKeyBoadDown(KEY_INPUT_D))
	{
		//bool���]
		m_isDebug = !m_isDebug;
		//�f�o�b�O���[�h�̏ꍇ
		if (m_isDebug)
		{
			//�f�o�b�O���[�h�J�n
			Init();
		}
		else
		{
			//�f�o�b�O�I��
			End();
		}
	}
}

void Debug::ChangeUnit()
{
	//�f�o�b�O���[�h�łȂ��ꍇ�A�������s��Ȃ�
	if (!m_isDebug) return;
	int index;
	VectorUtility::IsExistence(m_world.GetGameManager().GetUnitManager().GetVector(InfluenceID::ENEMY),m_targetUnit,index);
	int prevIndex = index;
	unsigned int max = m_world.GetGameManager().GetUnitManager().GetVector(InfluenceID::ENEMY).size();
	//���j�b�g��ύX����
	if (Input::GetInstance().IsKeyBoadDown(KEY_INPUT_UP))
	{
		index += max - 1;
	}
	else if (Input::GetInstance().IsKeyBoadDown(KEY_INPUT_DOWN))
	{
		index++;
	}
	index %= max;

	//���j�b�g�̕ύX���Ȃ��ꍇ�A�J�����̍Đ������s��Ȃ�
	if (prevIndex == index) return;
	m_targetUnit = m_world.GetGameManager().GetUnitManager().GetVector(InfluenceID::ENEMY)[index];
}

void Debug::CameraTargetChange()
{
	if (!Input::GetInstance().IsKeyBoadDown(KEY_INPUT_LEFT) && !Input::GetInstance().IsKeyBoadDown(KEY_INPUT_RIGHT)) return;
	if (m_target == CameraTarget::UNIT)
	{
		m_target = CameraTarget::CURSOR;

		m_camera->SetTarget([&]() {return m_cursor.Position(); });
	}
	else
	{
		m_target = CameraTarget::UNIT;
		m_camera->SetTarget([&]() {return m_targetUnit->Position(); });
	}
}
