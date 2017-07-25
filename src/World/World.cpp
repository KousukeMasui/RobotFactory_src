#include"World.h"
#include"Actor/Base/ActorGroup.h"
#include"Effect/Manager/EffectManager.h"
#include"Actor/Light/Light.h"
#include"PartsCreater\PartsCreater.h"
#include"CSVReader/CSVReader.h"
//コンストラクタ
World::World() :
	m_actors(),
	m_UIManager(),
	m_gameManager(nullptr),
	m_isPouse(false),
	m_isUIDraw(false),
	m_cameraMode(CameraMode::NORMAL),
	m_field(nullptr),
	m_effectManager(std::make_shared<EffectManager>()),
	m_billBoardManager(this)
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
	CSVReader csv("res/csv/factoryPosition.csv");

	for (int row = 1; row < csv.rows(); row++)
	{
		InfluenceID id;
		if (csv.get(row, 0) == "NONE") id = InfluenceID::NONE;
		if (csv.get(row, 0) == "PLAYER") id = InfluenceID::PLAYER;
		if (csv.get(row, 0) == "ENEMY") id = InfluenceID::ENEMY;
		m_gameManager->AddUnitFactory(*this, id, MyVector3(csv.getf(row, 1), csv.getf(row, 2), csv.getf(row, 3)));
	}
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