#include "GameManager.h"

#include"Actor\Unit\Unit.h"
#include"Actor\Parts\Parts.h"
#include"Actor/UnitFactory/UnitFactory.h"
#include"Math\Collision\HitInfo\HitInfo.h"
#include"Actor\Unit/Base\HP\Hp_Draw.h"
#include"Actor/Unit/AITree/Node/UnitNodeID.h"
#include"Actor/UnitFactory/UnitFactory.h"
#include"Actor/Influence/Player/Player.h"
#include"Actor/Influence/Enemy/Enemy.h"
#include"World/World.h"
GameManager::GameManager() :
	m_metaAI()
{
	//工場の初期値を読み込み 工場はゲームスタート前に生成されるので先にロードする
	m_csvData.Start("res/csv/factoryStatus.csv");
	m_csvData.Set(DATA_TYPE::FLOAT,CSV_DATA_ID::FACTORY_MAX_HP, Point2(0, 1));
	m_csvData.Set(DATA_TYPE::INT,CSV_DATA_ID::FACTORY_INIT_PARTS, Point2(1, 1));
	m_csvData.Set(DATA_TYPE::INT,CSV_DATA_ID::FACTORY_HEAL_INTERVAL_SECOND, Point2(2, 1));
	m_csvData.Set(DATA_TYPE::INT,CSV_DATA_ID::FACTORY_INIT_UNIT_HP, Point2(3, 1));
	m_csvData.Set(DATA_TYPE::INT,CSV_DATA_ID::FACTORY_INIT_UNIT_ATK, Point2(4, 1));
	m_csvData.Set(DATA_TYPE::INT,CSV_DATA_ID::FACTORY_INIT_UNIT_SPD, Point2(5, 1));
	m_csvData.Set(DATA_TYPE::INT,CSV_DATA_ID::FACTORY_INIT_HEAL_RANGE, Point2(6, 1));
	m_csvData.Set(DATA_TYPE::INT,CSV_DATA_ID::FACTORY_INIT_HEAL_POWER, Point2(7, 1));
	m_csvData.Set(DATA_TYPE::INT,CSV_DATA_ID::FACTORY_INIT_CREATE, Point2(8, 1));
	m_csvData.End();
}

GameManager::~GameManager()
{
}

void GameManager::GameStart(World& world)
{
	m_metaAI.Start(this);

	CSVLoad();

	//初期ユニット
	m_unitManager.Add(InfluenceID::PLAYER, std::make_shared<Unit>(world,m_metaAI.GetFind(), InfluenceID::PLAYER, 
		MyVector3(400.0f, 0.0f, 792.0f), UnitStatus(1, 1, 1, 10.0f,this)));
	m_unitManager.Add(InfluenceID::ENEMY, std::make_shared<Unit>(world, m_metaAI.GetFind(), InfluenceID::ENEMY,
		MyVector3(1250.0f, 0.0f, 792.0f), UnitStatus(1, 1, 1, 10.0f, this)));

	//プレイヤー生成
	m_influenceManager.Add(InfluenceID::PLAYER, std::make_shared<Player>(world));

	//エネミーユニット命令クラス生成
	auto enemy = std::make_shared<Enemy>(world);
	world.DebugSet(&*enemy);
	m_influenceManager.Add(InfluenceID::ENEMY, enemy);

	m_hp = std::make_shared<Hp_Draw>(world);

}

void GameManager::AddUnit(InfluenceID influence, const std::shared_ptr<Unit>& unit)
{
	m_unitManager.Add(influence,unit);
}

void GameManager::AddUnitFactory(IWorld & world, InfluenceID influence, const MyVector3 & position)
{
	m_factoryManager.Add(influence, std::make_shared<UnitFactory>(world,GetMetaAI().GetFind(), influence, position, m_factoryManager));
	
}
void GameManager::AddParts(const std::shared_ptr<Parts>& parts)
{
	m_partsManager.Add(0, parts);
}

UnitManager & GameManager::GetUnitManager()
{
	return m_unitManager;
}

PartsManager & GameManager::GetPartsManager()
{
	return m_partsManager;
}

FactoryManager & GameManager::GetFactoryManager()
{
	return m_factoryManager;
}
void GameManager::Update(float deltaTime)
{
	UnitUpdate(deltaTime);
	m_influenceManager.Update(deltaTime);
	auto units = m_unitManager.All();

	m_unitManager.Function(
		[&](std::shared_ptr<Unit> unit)
	{
		for (auto other : units)
		{
			//自分との判定は早期リターン
			if (other == unit) continue;
			if (unit->IsDead() || other->IsDead()) continue;//どちらかが死んでいる場合終了
			if (unit->IsCollide(*other))
			{
				unit->Collide(*other);
			}
		}
	});
	m_factoryManager.Update(deltaTime);
	auto noneInfluenceFactorys = m_factoryManager.GetVector(InfluenceID::NONE);
	for (auto itr = noneInfluenceFactorys.begin(); itr != noneInfluenceFactorys.end(); ++itr)
	{
		itr->get()->NonInfluenceUpdate(deltaTime);
	}

	m_partsManager.Remove();

	m_metaAI.Update(deltaTime);
}

void GameManager::Draw() const
{
	m_influenceManager.Draw();
	m_unitManager.Draw();
	m_partsManager.Draw();
	m_factoryManager.Draw();
	if (m_hp == nullptr) return;
	m_hp->Clear();
	//HPの表示
	m_unitManager.Function([&](const UnitPtr& unit) {
		m_hp->Set(unit->GetStatus().Status(UNIT_STATUS_ID::MAX_HP), unit->GetStatus().Status(UNIT_STATUS_ID::HP),
			MyVector2(100.0f, 40.0f), unit->Position() + MyVector3(0.0f, 20.0f, 0.0f));
	});
	m_factoryManager.Function([&](const FactoryPtr& factory) {
		m_hp->Set(factory->Status().maxHP, factory->Status().hp, MyVector2(150, 60), factory->GetParam().Position() + MyVector3(0, 100.0f, 0.0f));
	});
	m_hp->Draw();
	//m_spriteManager.Draw();
}

CSVData & GameManager::GetCSV()
{
	return m_csvData;
}

MetaAI & GameManager::GetMetaAI()
{
	return m_metaAI;
}

void GameManager::UnitUpdate(float deltaTime)
{

	UnitPtrs tmp;
	//生成演出の工場から出る処理が終わったらtmpに追加
	m_unitManager.Function(InfluenceID::EFFECT, [&](UnitPtr unit) {
		if (!unit->Agent().IsMove())
		{
			tmp.push_back(unit);
		}
	});
	//tmpの中身をその勢力のユニットにする
	for (auto unit : tmp) {
		m_unitManager.Move(InfluenceID::EFFECT, unit->GetInfluence(), &*unit);
	}
	m_unitManager.Update(deltaTime);
}

void GameManager::CSVLoad()
{
	//csv読み込み
	m_csvData.Start("res/csv/unitParameter.csv");
	m_csvData.Set(DATA_TYPE::FLOAT, CSV_DATA_ID::UNIT_RADIUS, Point2(0, 1), 2);
	m_csvData.Set(DATA_TYPE::FLOAT, CSV_DATA_ID::UNIT_HEIGHT, Point2(1, 1), 2);
	m_csvData.Set(DATA_TYPE::FLOAT, CSV_DATA_ID::UNIT_ATTACK_RANGE, Point2(2, 1), 2);
	m_csvData.Set(DATA_TYPE::FLOAT, CSV_DATA_ID::UNIT_LIFT_RANGE, Point2(3, 1), 2);
	m_csvData.End();
	//ユニットの強化時のステータスを読み込み
	m_csvData.Start("res/csv/unitLevelParameter.csv");
	m_csvData.Set(DATA_TYPE::FLOAT, CSV_DATA_ID::UNIT_HP, Point2(1, 1));
	m_csvData.Set(DATA_TYPE::FLOAT, CSV_DATA_ID::UNIT_ATK, Point2(2, 1));
	m_csvData.Set(DATA_TYPE::FLOAT, CSV_DATA_ID::UNIT_SPD, Point2(3, 1));
	m_csvData.End();
	//ユニットの勢力毎の色を読み込み
	m_csvData.Start("res/csv/unitColor.csv");
	m_csvData.Set(DATA_TYPE::INT, CSV_DATA_ID::UNIT_COLOR_CHANGE_INDICES, Point2(0, 1));

	m_csvData.Set(DATA_TYPE::FLOAT, CSV_DATA_ID::PLAYER_COLOR, Point2(1, 1),5);
	m_csvData.Set(DATA_TYPE::FLOAT, CSV_DATA_ID::PLAYER_AMBIENT_COLOR, Point2(2, 1), 5);
	m_csvData.Set(DATA_TYPE::FLOAT, CSV_DATA_ID::ENEMY_COLOR, Point2(3, 1), 5);
	m_csvData.Set(DATA_TYPE::FLOAT, CSV_DATA_ID::ENEMY_AMBIENT_COLOR, Point2(4,1), 5);
	m_csvData.End();
}
