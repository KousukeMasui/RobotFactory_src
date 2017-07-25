#include "FactoryUI.h"
#include"Resources.h"
#include"UI/Sprite/Sprite.h"
#include"UI/Sprite/Action/MouseClickFunc/MouseClickFunc.h"
#include"Input\Mouse\Mouse.h"
#include"UI/UIAction/UpdateAction/UpdateAction.h"
#include"Actor\UnitFactory\UnitFactory.h"
#include"UI/Sprite/Number/NumberDraw.h"
#include"Actor\Influence\Player\Player.h"
#include"Scene/GamePlay/GamePlaySpriteID.h"
#include"Actor/UnitFactory/FactoryStatusID.h"
#include"Screen/Screen.h"
FactoryUI::FactoryUI(IWorld& world):
	m_world(world),
	m_factory(nullptr)
{
	m_status[TEXTURE_ID::CREATE] = FactoryStatusID::CREATE;
	m_status[TEXTURE_ID::HP_UP] = FactoryStatusID::UNIT_HP;
	m_status[TEXTURE_ID::ATTACK_UP] = FactoryStatusID::UNIT_ATK;
	m_status[TEXTURE_ID::SPEED_UP] = FactoryStatusID::UNIT_SPD;
	m_status[TEXTURE_ID::HEAL_POWER] = FactoryStatusID::HEAL_POWER;
	m_status[TEXTURE_ID::HEAL_RANGE] = FactoryStatusID::HEAL_RANGE;
	Initialize();
}

FactoryUI::~FactoryUI()
{
}
void FactoryUI::Update(float deltaTime)
{
	//変数の初期化
	m_deleteFunc = []() {};
	m_manager.Update(deltaTime);
	m_deleteFunc();//削除実行
}
void FactoryUI::StatusGaugeDraw() const
{
	GaugeDraw(m_sprites.at((int)TEXTURE_ID::HP_UP)->Position() ,m_sprites.at((int)TEXTURE_ID::HP_UP)->TexSize(), m_factory->Status().status[FactoryStatusID::UNIT_HP]);
	GaugeDraw(m_sprites.at((int)TEXTURE_ID::ATTACK_UP)->Position() , m_sprites.at((int)TEXTURE_ID::ATTACK_UP)->TexSize(), m_factory->Status().status[FactoryStatusID::UNIT_ATK]);
	GaugeDraw(m_sprites.at((int)TEXTURE_ID::SPEED_UP)->Position() , m_sprites.at((int)TEXTURE_ID::SPEED_UP)->TexSize(), m_factory->Status().status[FactoryStatusID::UNIT_SPD]);
}

void FactoryUI::HealGaugeDraw() const
{
	GaugeDraw(m_sprites.at((int)TEXTURE_ID::HEAL_POWER)->Position(), m_sprites.at((int)TEXTURE_ID::HEAL_POWER)->TexSize(), m_factory->Status().status[FactoryStatusID::HEAL_POWER]);
	GaugeDraw(m_sprites.at((int)TEXTURE_ID::HEAL_RANGE)->Position(), m_sprites.at((int)TEXTURE_ID::HEAL_RANGE)->TexSize(), m_factory->Status().status[FactoryStatusID::HEAL_RANGE]);
}												   

//UIを作成する関数
void FactoryUI::Create(const FactoryPtr& factory)
{
	m_factory = factory;
	FirstCommand();
}

void FactoryUI::Delete(GamePlaySpriteID createID)
{
	std::vector<int> IDs;
	switch (createID)
	{
	case GamePlaySpriteID::COMMAND_FIRST:
		IDs.push_back((int)GamePlaySpriteID::COMMAND_FACTORY);
		IDs.push_back((int)GamePlaySpriteID::COMMAND_UNIT);
		break;
	case GamePlaySpriteID::COMMAND_FACTORY:
		IDs.push_back((int)GamePlaySpriteID::COMMAND_FIRST);
		IDs.push_back((int)GamePlaySpriteID::COMMAND_UNIT);
		break;
	case GamePlaySpriteID::COMMAND_UNIT:
		IDs.push_back((int)GamePlaySpriteID::COMMAND_FACTORY);
		IDs.push_back((int)GamePlaySpriteID::COMMAND_FIRST);
		break;
	}

	for (auto id : IDs)
		m_manager.DeleteSprite(id);
}

void FactoryUI::Delete()
{
	m_manager.Clear();
}

void FactoryUI::Draw() const
{
	switch (m_command)
	{
	case DrawCommand::COMMAND_STATUS:
		StatusGaugeDraw();
		break;
	case DrawCommand::COMMAND_HEAL:
		HealGaugeDraw();
		break;
	default:
		//生成に必要な資源の表示
		NumberDraw::Draw(m_sprites.at((int)TEXTURE_ID::CREATE)->Position() + MyVector2(0,m_sprites.at((int)TEXTURE_ID::CREATE)->TexSize().y), 2, m_factory->Status().CreatePartsCount(), 0.2f);
		break;
	}

	//資源数の描画
	NumberDraw::Draw(m_sprites.at((int)TEXTURE_ID::PARTS)->Position() + MyVector2(m_sprites.at((int)TEXTURE_ID::PARTS)->TexSize().x,0), 3, m_factory->PartsCount());
	
	m_manager.Draw();
}

bool FactoryUI::IsAuto() const
{
	return m_command == DrawCommand::COMMAND_HEAL && Mouse::GetInstance().IsPressUp(MouseCommand::LEFT) &&
		m_sprites.at((int)TEXTURE_ID::AUTO)->IsCollide(Mouse::GetInstance().Position());
}

void FactoryUI::GaugeDraw(MyVector2 startPosition,MyVector2 texSize, int size) const
{
	for (int i = 0; i < 20; i++)
	{
		m_sprites.at((int)TEXTURE_ID::COMMAND_FRAME)->Position(startPosition+ MyVector2(texSize.x,0) + 15.0f* i);
		m_sprites.at((int)TEXTURE_ID::COMMAND_FRAME)->Draw();
	}

	for (int i = 0; i < size; i++)
	{
		m_sprites.at((int)TEXTURE_ID::COMMAND_GAUGE)->Position(startPosition+ MyVector2(texSize.x, 0) + 15.0f * i);
		m_sprites.at((int)TEXTURE_ID::COMMAND_GAUGE)->Draw();
	}
	//消費資源数の描画
	NumberDraw::Draw(startPosition + texSize, 2,size,0.2f);

}

void FactoryUI::Initialize()
{
	//マウスが上にある時に色を変えるaction
	auto onMouseColor = std::make_shared<MouseClickFunc>(
		[&](Sprite* sprite)
	{
		//マウスが乗っている時に、色を変える
		sprite->SetColor(Color(0.8f, 0.8f, 0.8f));
		if (Mouse::GetInstance().IsPressState(MouseCommand::LEFT))
		{
			sprite->SetColor(Color(0.5f, 0.5f, 0.5f));
		}
	},
		[&](Sprite* sprite)
	{
		sprite->SetColor(Color(1.0f, 1.0f, 1.0f, 1.0f));
	});

	auto statusAction = std::make_shared<SameTime>(2, onMouseColor, CreateStatusAction());
	//ユニットステータス画像
	{
		SpritePtr hp, atk, spd;

		//HP画像
		{
			hp = std::make_shared<Sprite>(TEXTURE_ID::HP_UP, MyVector2(0, 350), MyVector2(1, 1), MyVector2(0.5f, 0.5f));
			hp->SetAction(statusAction);

			m_sprites[(int)TEXTURE_ID::HP_UP] = hp;
		}
		//攻撃画像
		{
			atk = std::make_shared<Sprite>(TEXTURE_ID::ATTACK_UP, MyVector2(0, 250), MyVector2(1, 1), MyVector2(0.5f, 0.5f));

			atk->SetAction(statusAction);
			m_sprites[(int)TEXTURE_ID::ATTACK_UP] = atk;
		}
		//速度画像
		{
			spd = std::make_shared<Sprite>(TEXTURE_ID::SPEED_UP, MyVector2(0, 450), MyVector2(1, 1), MyVector2(0.5f, 0.5f));

			spd->SetAction(statusAction);
			m_sprites[(int)TEXTURE_ID::SPEED_UP] = spd;
		}
		//ステータス画像
		auto status = std::make_shared<Sprite>(TEXTURE_ID::UNIT, MyVector2(50, 10), MyVector2(1, 1), MyVector2(0.5f, 0.5f));
		auto click = std::make_shared<MouseClickFunc>(
			[&](Sprite* sprite)
		{
			if (Mouse::GetInstance().IsPressUp(MouseCommand::LEFT))
			{
				m_deleteFunc = [&]() {
					StatusCommand();
				};
			}
		});
		auto same = std::make_shared<SameTime>(2, onMouseColor, click);
		status->SetAction(same);

		m_sprites[(int)TEXTURE_ID::UNIT] = status;
	}

	//回復ステータス画像
	{
		SpritePtr power, range;
		//回復力
		{
			power = std::make_shared<Sprite>(TEXTURE_ID::HEAL_POWER, MyVector2(0, 250), MyVector2(1, 1), MyVector2(0.5f, 0.5f));
			
			power->SetAction(statusAction);

			m_sprites[(int)TEXTURE_ID::HEAL_POWER] = power;
		}
		//回復範囲
		{
			range = std::make_shared<Sprite>(TEXTURE_ID::HEAL_RANGE, MyVector2(0, 350), MyVector2(1, 1), MyVector2(0.5f, 0.5f));
			
			range->SetAction(statusAction);

			m_sprites[(int)TEXTURE_ID::HEAL_RANGE] = range;
		}

		auto heal = std::make_shared<Sprite>(TEXTURE_ID::FACTORY, MyVector2(50, 200), MyVector2(1, 1), MyVector2(0.5f, 0.5f));
		auto click = std::make_shared<MouseClickFunc>(
			[&](Sprite* sprite)
		{
			if (Mouse::GetInstance().IsPressUp(MouseCommand::LEFT))
			{
				m_deleteFunc = [&](){
				HealCommand(); 
				};
			}
		});
		auto same = std::make_shared<SameTime>(2, onMouseColor, click);
		heal->SetAction(same);

		m_sprites[(int)TEXTURE_ID::FACTORY] = heal;

	}
	//生成画像
	{
		auto create = std::make_shared<Sprite>
			(TEXTURE_ID::CREATE, MyVector2(50, 390), MyVector2(1, 1), MyVector2());
		create->SetAction(statusAction);

		m_sprites[(int)TEXTURE_ID::CREATE] = create;
	}
	//資源画像
	{
		auto parts = std::make_shared<Sprite>(TEXTURE_ID::PARTS, MyVector2(1000, 610), MyVector2(1, 1), MyVector2(0.5f, 0.5f));

		m_sprites[(int)TEXTURE_ID::PARTS] = parts;
	}
	//閉じる画像
	{
		auto close = std::make_shared<Sprite>
			(TEXTURE_ID::CLOSE, MyVector2(1000, 10), MyVector2(1, 1), MyVector2());
		//クリックでUIを削除
		auto click = std::make_shared<MouseClickFunc>(
			[&](Sprite* sprite)
		{
			if (Mouse::GetInstance().IsPressUp(MouseCommand::LEFT))
			{
				m_world.Command();
			}

		});
		auto same = std::make_shared<SameTime>(2, onMouseColor, click);
		close->SetAction(same);

		m_sprites[(int)TEXTURE_ID::CLOSE] = close;
	}
	//戻るボタン
	{
		auto back = std::make_shared<Sprite>
			(TEXTURE_ID::BACK, MyVector2(10, 10), MyVector2(1, 1), MyVector2());
		//クリックでUIを削除
		auto click = std::make_shared<MouseClickFunc>(
			[&](Sprite* sprite)
		{
			if (Mouse::GetInstance().IsPressUp(MouseCommand::LEFT))
			{
				if (m_command != DrawCommand::COMMAND_AUTO)
					m_deleteFunc = [&]() {
					FirstCommand();
				};
				else
					m_deleteFunc = [&]() {
					HealCommand();
				};
			}

		});
		auto same = std::make_shared<SameTime>(2, onMouseColor, click);
		back->SetAction(same);

		m_sprites[(int)TEXTURE_ID::BACK] = back;
	}

	//背景画像
	{
		auto back = std::make_shared<Sprite>
			(TEXTURE_ID::BLACK, MyVector2(), MyVector2((float)Screen::SCREEN_SIZE.x, (float)Screen::SCREEN_SIZE.y), MyVector2(0.0f, 0.0f));
		back->Alpha(0.5f);
		m_sprites[(int)TEXTURE_ID::BLACK] = back;
	}

	//バー画像
	{
		m_sprites[(int)TEXTURE_ID::COMMAND_FRAME] = std::make_shared<Sprite>(TEXTURE_ID::COMMAND_FRAME, MyVector2(), MyVector2(1.0f, 1), MyVector2(0.5f, 0.5f));
	
		m_sprites[(int)TEXTURE_ID::COMMAND_GAUGE] = std::make_shared<Sprite>(TEXTURE_ID::COMMAND_GAUGE, MyVector2(), MyVector2(1, 1), MyVector2(0.5f, 0.5f));
	}

	//Autoボタン
	{
		SpritePtr autoSprite;
		autoSprite = std::make_shared<Sprite>(TEXTURE_ID::AUTO, MyVector2(0,450), MyVector2(1, 1), MyVector2(0.5f, 0.5f));
		auto click = std::make_shared<MouseClickFunc>([&](Sprite* sprite) 
		{
			if (!Mouse::GetInstance().IsPressUp(MouseCommand::LEFT)) return;

			//戻るボタンのみ生成
			//Delete();
			//m_manager.AddSprite((int)TEXTURE_ID::BACK, m_sprites[(int)TEXTURE_ID::BACK]);
			//m_command = DrawCommand::COMMAND_AUTO;
		});

		auto same = std::make_shared<SameTime>(2, onMouseColor, click);
		autoSprite->SetAction(same);
		m_sprites[(int)TEXTURE_ID::AUTO] = autoSprite;
	}
}

void FactoryUI::FirstCommand()
{
	int id = (int)GamePlaySpriteID::COMMAND_FIRST;
	Delete(GamePlaySpriteID::COMMAND_FIRST);
	m_manager.AddSprite(id, m_sprites[(int)TEXTURE_ID::UNIT]);
	m_manager.AddSprite(id, m_sprites[(int)TEXTURE_ID::FACTORY]);
	m_manager.AddSprite(id, m_sprites[(int)TEXTURE_ID::CREATE]);
	m_manager.AddSprite(id, m_sprites[(int)TEXTURE_ID::CLOSE]);
	m_manager.AddSprite(id, m_sprites[(int)TEXTURE_ID::PARTS]);

	m_manager.AddSprite(id, m_sprites[(int)TEXTURE_ID::BLACK]);
	m_command = DrawCommand::COMMAND_FIRST;
}

void FactoryUI::StatusCommand()
{
	Delete(GamePlaySpriteID::COMMAND_UNIT);
	int id = (int)GamePlaySpriteID::COMMAND_UNIT;
	m_manager.AddSprite(id, m_sprites[(int)TEXTURE_ID::HP_UP]);
	m_manager.AddSprite(id, m_sprites[(int)TEXTURE_ID::ATTACK_UP]);
	m_manager.AddSprite(id, m_sprites[(int)TEXTURE_ID::SPEED_UP]);
	m_manager.AddSprite(id, m_sprites[(int)TEXTURE_ID::BACK]);

	m_manager.AddSprite(id, m_sprites[(int)TEXTURE_ID::PARTS]);
	m_manager.AddSprite(id, m_sprites[(int)TEXTURE_ID::CLOSE]);

	m_manager.AddSprite(id, m_sprites[(int)TEXTURE_ID::BLACK]);
	m_command = DrawCommand::COMMAND_STATUS;
}

void FactoryUI::HealCommand()
{
	Delete(GamePlaySpriteID::COMMAND_FACTORY);
	int id = (int)GamePlaySpriteID::COMMAND_FACTORY;

	m_manager.AddSprite(id, m_sprites[(int)TEXTURE_ID::HEAL_POWER]);
	m_manager.AddSprite(id, m_sprites[(int)TEXTURE_ID::HEAL_RANGE]);
	m_manager.AddSprite(id, m_sprites[(int)TEXTURE_ID::AUTO]);
	m_manager.AddSprite(id, m_sprites[(int)TEXTURE_ID::BACK]);

	m_manager.AddSprite(id, m_sprites[(int)TEXTURE_ID::PARTS]);
	m_manager.AddSprite(id, m_sprites[(int)TEXTURE_ID::CLOSE]);

	m_manager.AddSprite(id, m_sprites[(int)TEXTURE_ID::BLACK]);
	m_command = DrawCommand::COMMAND_HEAL;
}

std::shared_ptr<SameTime> FactoryUI::CreateStatusAction()
{
	auto isStatusColor = std::make_shared<UpdateAction>(
		[&](UI* ui)
	{
		Sprite* sprite = (Sprite*)ui;
		if (!m_factory->Status().IsStatusUp(m_status[sprite->TexID()]))
		{
			sprite->SetColor(Color(0.5f, 0.5f, 0.5f));
		}
	});

	auto click = std::make_shared<MouseClickFunc>(
		[&](Sprite* sprite)
	{
		if (Mouse::GetInstance().IsPressUp(MouseCommand::LEFT) && m_factory->Status().IsStatusUp(m_status[sprite->TexID()]))
		{
			m_factory->StatusUp(m_status[sprite->TexID()]);
		}
	});
	return std::make_shared<SameTime>(2, isStatusColor, click);
}
