#pragma once

#include"Base/Manager/TemplateManager.h"
#include"Math\Vector/MyVector3.h"
#include"Actor\Parts\Parts.h"
#include"Actor\Influence\InfluenceID.h"
#include"FactoryManager.h"
#include"UnitManager.h"
#include"CSVReader/CSVData.h"
#include"Actor/Influence/AIAction/MetaAI/MetaAI.h"
class Influence;
class Hp_Draw;
typedef TemplateManager<int, Parts, MyVector3> PartsManager;
typedef TemplateManager<InfluenceID, Influence, int> InfluenceManager;
class Enemy;
class World;
class WorldToSpriteManager;
//IsDelete() GetParam()は必須なので注意
//今回のゲームにのみ使うmanagerクラスの統括クラス
class GameManager
{
public:
	GameManager();
	~GameManager();
	//ゲーム開始
	void GameStart(World& world);
	//追加関数
	void AddUnit(InfluenceID influence,const std::shared_ptr<Unit>& unit);
	void AddUnitFactory(IWorld& world, InfluenceID influence, const MyVector3& position);
	void AddParts(const std::shared_ptr<Parts>& parts);

	//取得関数
	UnitManager& GetUnitManager();
	PartsManager& GetPartsManager();
	FactoryManager& GetFactoryManager();
	//更新
	void Update(float deltaTime);
	//描画
	void Draw() const;
	//csvデータ引き渡し
	CSVData& GetCSV();
	MetaAI& GetMetaAI();
private:
	void UnitUpdate(float deltaTime);
private:
	UnitManager m_unitManager;
	PartsManager m_partsManager;
	FactoryManager m_factoryManager;
	//勢力管理クラス
	InfluenceManager m_influenceManager;
	std::shared_ptr<Hp_Draw> m_hp;
	//csv情報保存クラス
	CSVData m_csvData;
	//メタAI
	MetaAI m_metaAI;
};