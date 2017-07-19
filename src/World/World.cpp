#include"World.h"
#include"Actor/Base/ActorGroup.h"
#include"Effect/Manager/EffectManager.h"
#include"Actor/Light/Light.h"
#include"PartsCreater\PartsCreater.h"
//コンストラクタ
World::World() :
	m_actors(),
	m_UIManager(),
	m_gameManager(nullptr),
	m_isPouse(false),
	m_isUIDraw(false),
	m_fieldMap(),
	m_cameraMode(CameraMode::NORMAL),
	m_field(nullptr),
	m_effectManager(std::make_shared<EffectManager>()),
	m_billBoardManager(this),
	m_metaAI()
{
}


//更新
void World::Update(float deltaTime)
{
	m_UIManager.Update(deltaTime);
	if (m_isPouse)
	{
		//m_player->AutoSelectUpdate(deltaTime);
	}
	else
	{
		m_actors.Update(deltaTime);
		m_gameManager->Update(deltaTime);

		m_effectManager->Update(deltaTime);

		//m_field->Update(deltaTime);
		m_camera[m_cameraMode]->Update(deltaTime);
		if(m_debug!= nullptr) m_debug->Update(deltaTime);
	}
	m_billBoardManager.Update();

	m_metaAI.Update();
}

//描画
void World::Draw() const
{
	m_light->Draw();
	m_camera.at(m_cameraMode)->Draw();
	m_field->Draw();
	m_actors.Draw();

	m_gameManager->Draw();
	m_effectManager->Draw();
	m_billBoardManager.Draw();
	m_UIManager.Draw();
	
	//if (m_debug != nullptr)
	//{
	//	clsDx();
	//	if (m_debug->IsDebug())
	//	{
	//		printfDx("\n\nDキー : 通常モードに");
	//		m_debug->Draw();
	//	}
	//	else
	//		printfDx("\n\nDキー : デバッグモードに");
	//}

}

void World::StageCreate()
{
	m_gameManager = std::make_shared<GameManager>();
	m_gameManager->AddUnitFactory(*this, InfluenceID::NONE, MyVector3(606.0f, 0.0f, 356.0f));
	m_gameManager->AddUnitFactory(*this, InfluenceID::NONE, MyVector3(1108.0f, 0.0f, 512.0f));
	m_gameManager->AddUnitFactory(*this, InfluenceID::NONE, MyVector3(528.0f, 0.0f, 1258.0f));
	m_gameManager->AddUnitFactory(*this, InfluenceID::NONE, MyVector3(1091.0f, 0.0f, 1085.0f));

	m_gameManager->AddUnitFactory(*this, InfluenceID::PLAYER, MyVector3(312.0f, 0.0f, 835.0f));
	m_gameManager->AddUnitFactory(*this, InfluenceID::ENEMY, MyVector3(1348.0f, 0.0f, 790.0f));

	m_metaAI.Start(&*m_gameManager);
	AddLight(std::make_shared<Light>(*this, MyVector3(451.1f, 290.28f, 843.94f)));
	m_field = std::make_shared<Field>();
}

void World::GameStart()
{
	m_gameManager->GameStart(*this);

	AddActor(ActorGroup::PARTS_CREATER, std::make_shared<PartsCreater>(*this));
}

void World::GameEnd()
{
	m_UIManager.Clear();
	m_isUIDraw = false;
	m_isPouse = false;
	m_billBoardManager.Delete();
}

void World::GameReset()
{
	m_gameManager = nullptr;
	m_field = nullptr;
	m_light = nullptr;
	m_actors.Clear();
}

//カメラの追加
void World::AddCamera(CameraMode mode,const std::shared_ptr<Camera>& camera)
{
	m_camera[mode] = camera;
}

void World::SetCamera(CameraMode mode)
{
	m_cameraMode = mode;
}

std::shared_ptr<Camera> World::GetCamera() const
{
	return m_camera.at(m_cameraMode);
}

//ライトの追加
void World::AddLight(const ActorPtr& light)
{
	m_light = light;
}
std::shared_ptr<Field> World::GetField() const
{
	return m_field;
}

//メッセージの送信
void World::MessageSend(EventMessage message, void* param)
{
	HandleMessage(message, param);
}

//メッセージ処理
void World::HandleMessage(EventMessage message, void* param)
{
	m_actors.HandleMessage(message, param);
}

//アクターの追加
void World::AddActor(ActorGroup group, const ActorPtr& actor)
{
	m_actors.AddActor(group, actor);
}

//アクターの検索
ActorPtr World::FindActor(const std::string& name)
{
	return m_actors.FindActor(name);
}

std::vector<ActorPtr> World::FindActors(const ActorGroup & group)
{
	return m_actors.FindActors(group);
}

UIManager & World::GetUIManager()
{
	return m_UIManager;
}

GameManager & World::GetGameManager()
{
	return *m_gameManager;
}

FieldMap & World::GetFieldMap()
{
	return m_fieldMap;
}
void World::DebugSet(Enemy * enemy)
{
	m_debug = std::make_shared<Debug>(*this, enemy->Cursor());
}

std::shared_ptr<Effect3D> World::CreateEffect(EffectID effect)
{
	return m_effectManager->CreateEffect(effect);
}

BillBoardManager & World::GetBillBoardManager()
{
	return m_billBoardManager;
}

void World::Command(const FactoryPtr & factory)
{
	m_commandFactory = factory;
}

bool World::IsCommand() const
{
	return m_commandFactory != nullptr;
}

FactoryPtr World::GetCommandFactory() const
{
	return m_commandFactory;
}

MetaAI & World::GetMetaAI()
{
	return m_metaAI;
}
