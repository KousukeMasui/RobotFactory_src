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
	ChangeDebug();//デバッグモードと通常モードの切り替え
	//カメラのターゲットの種類を変更
	CameraTargetChange();
	ChangeUnit();//カメラのユニットを変更
}

void Debug::Draw() const
{
	//printfDx("\n\n");
	//printfDx("左右キーでユニットとカーソルの変更\n");
	//printfDx("上下キーでユニット変更\n\n\n");
	//移動中のオブジェクトのみ目的地を描画
	if (m_targetUnit->IsMove())
	{
		//m_unitTarget.Draw(m_targetUnit->GetParam().roadPositions.front() + MyVector3(0, 2, 0), MyVector3(13, 1, 13), 0.0f);
	}
}

void Debug::Init()
{
	//カメラをユニット追従カメラに変更
	m_world.SetCamera(CameraMode::UNIT);
}

void Debug::End()
{
	//カメラを通常カメラに変更
	m_world.SetCamera(CameraMode::NORMAL);
}

void Debug::ChangeDebug()
{
	if (Input::GetInstance().IsKeyBoadDown(KEY_INPUT_D))
	{
		//bool反転
		m_isDebug = !m_isDebug;
		//デバッグモードの場合
		if (m_isDebug)
		{
			//デバッグモード開始
			Init();
		}
		else
		{
			//デバッグ終了
			End();
		}
	}
}

void Debug::ChangeUnit()
{
	//デバッグモードでない場合、処理を行わない
	if (!m_isDebug) return;
	int index;
	VectorUtility::IsExistence(m_world.GetGameManager().GetUnitManager().GetVector(InfluenceID::ENEMY),m_targetUnit,index);
	int prevIndex = index;
	unsigned int max = m_world.GetGameManager().GetUnitManager().GetVector(InfluenceID::ENEMY).size();
	//ユニットを変更する
	if (Input::GetInstance().IsKeyBoadDown(KEY_INPUT_UP))
	{
		index += max - 1;
	}
	else if (Input::GetInstance().IsKeyBoadDown(KEY_INPUT_DOWN))
	{
		index++;
	}
	index %= max;

	//ユニットの変更がない場合、カメラの再生成を行わない
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
