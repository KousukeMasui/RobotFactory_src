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
//IsDelete() GetParam()�͕K�{�Ȃ̂Œ���
//����̃Q�[���ɂ̂ݎg��manager�N���X�̓����N���X
class GameManager
{
public:
	GameManager();
	~GameManager();
	//�Q�[���J�n
	void GameStart(World& world);
	//�ǉ��֐�
	void AddUnit(InfluenceID influence,const std::shared_ptr<Unit>& unit);
	void AddUnitFactory(IWorld& world, InfluenceID influence, const MyVector3& position);
	void AddParts(const std::shared_ptr<Parts>& parts);

	//�擾�֐�
	UnitManager& GetUnitManager();
	PartsManager& GetPartsManager();
	FactoryManager& GetFactoryManager();
	//�X�V
	void Update(float deltaTime);
	//�`��
	void Draw() const;
	//csv�f�[�^�����n��
	CSVData& GetCSV();
	MetaAI& GetMetaAI();
private:
	void UnitUpdate(float deltaTime);
private:
	UnitManager m_unitManager;
	PartsManager m_partsManager;
	FactoryManager m_factoryManager;
	//���͊Ǘ��N���X
	InfluenceManager m_influenceManager;
	std::shared_ptr<Hp_Draw> m_hp;
	//csv���ۑ��N���X
	CSVData m_csvData;
	//���^AI
	MetaAI m_metaAI;
};