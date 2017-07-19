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
GameManager::GameManager()
{
}

GameManager::~GameManager()
{
}

void GameManager::GameStart(World& world)
{
	//�������j�b�g
	m_unitManager.Add(InfluenceID::PLAYER, std::make_shared<Unit>(world, InfluenceID::PLAYER, MyVector3(400.0f, 0.0f, 792.0f), UnitStatus(1, 10, 1, 1, 10.0f)));
	m_unitManager.Add(InfluenceID::ENEMY, std::make_shared<Unit>(world, InfluenceID::ENEMY, MyVector3(1250.0f, 0.0f, 792.0f), UnitStatus(1, 10, 1, 1, 10.0f)));

	//�v���C���[����
	m_influenceManager.Add(InfluenceID::PLAYER, std::make_shared<Player>(world));

	//�G�l�~�[���j�b�g���߃N���X����
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
	m_factoryManager.Add(influence, std::make_shared<UnitFactory>(world, influence, position, m_factoryManager));
	
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
			//�����Ƃ̔���͑������^�[��
			if (other == unit) continue;
			if (unit->IsDead() || other->IsDead()) continue;//�ǂ��炩������ł���ꍇ�I��
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
	m_factoryManager.Function(
		[&](std::shared_ptr<UnitFactory> factory)
	{
		auto units = m_unitManager.GetOther(InfluenceID::EFFECT);
		for (auto unit : units)
		{
			if (factory->IsCollide(*unit))
			{
				factory->Collide(*unit);
			}
		}
	});

	m_partsManager.Remove();
}

void GameManager::Draw() const
{
	m_influenceManager.Draw();
	m_unitManager.Draw();
	m_partsManager.Draw();
	m_factoryManager.Draw();
	if (m_hp == nullptr) return;
	m_hp->Clear();
	//HP�̕\��
	m_unitManager.Function([&](const UnitPtr& unit) {
		m_hp->Set(unit->GetStatus().maxHP, unit->GetStatus().hp, MyVector2(100, 40), unit->Position() + MyVector3(0, 20, 0));
	});
	m_factoryManager.Function([&](const FactoryPtr& factory) {
		m_hp->Set(factory->Status().maxHP, factory->Status().hp, MyVector2(150, 60), factory->GetParam().Position() + MyVector3(0, 100.0f, 0.0f));
	});
	m_hp->Draw();
	//m_spriteManager.Draw();
}

void GameManager::UnitUpdate(float deltaTime)
{
	UnitPtrs tmp;
	m_unitManager.Function(InfluenceID::EFFECT, [&](UnitPtr unit) {
		if (!unit->IsMove())
		{
			tmp.push_back(unit);
		}
	});
	for (auto unit : tmp) {
		m_unitManager.Move(InfluenceID::EFFECT, unit->GetInfluence(), &*unit);
	}
	m_unitManager.Update(deltaTime);
}