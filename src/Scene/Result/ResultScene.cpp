#include "ResultScene.h"
#include"../../World/World.h"
#include"Scene\Base\Scene.h"
#include"Input\Mouse\Mouse.h"
#include"UI/Sprite/Action/MouseClickFunc\MouseClickFunc.h"
#include"Loader/Loader.h"
ResultScene::ResultScene(const std::shared_ptr<World>& world,bool & isWin):
	m_world(world),
	m_isWin(isWin),
	m_nextScene(Scene::Title),
	m_isEnd(false)
{
}

ResultScene::~ResultScene()
{
}
void ResultScene::Initialize()
{
	m_UIManager = std::make_shared<UIManager>();
	m_isEnd = false;
	//�������ꍇ
	if (m_isWin)
	{
		Loader::GetInstance().TextureLoad(TEXTURE_ID::RESULT_TEXT, "res/Texture/Result/Win.png");
	}
	else
	{
		Loader::GetInstance().TextureLoad(TEXTURE_ID::RESULT_TEXT, "res/Texture/Result/Lose.png");
	}

	auto onMouse = std::make_shared<MouseClickFunc>(
		[&](Sprite* sprite)
	{
		sprite->SetColor(Color(1.0f, 1.0f, 1.0f, 1.0f));
		//�}�E�X������Ă��鎞�ɁA�F��ς���
		if (Mouse::GetInstance().IsPressState(MouseCommand::LEFT))
		{
			sprite->SetColor(Color(1.0f, 1.0f, 1.0f, 0.3f));
		}
	},
		[&](Sprite* sprite)
	{
		sprite->SetColor(Color(1.0f, 1.0f, 1.0f, 0.5f));
	});

	//sprite�̓o�^ result�͉摜=sprite�Ȃ̂�textureID�����̂܂ܓ����
	auto retry = std::make_shared<Sprite>(TEXTURE_ID::RETRY, MyVector2(250, 487), MyVector2(1, 1), MyVector2(0.5f, 0.5f));
	retry->SetAction(onMouse);
	m_UIManager->AddSprite((int)TEXTURE_ID::RETRY, retry);
	auto title  = std::make_shared<Sprite>(TEXTURE_ID::TO_TITLE, MyVector2(800, 487), MyVector2(1, 1), MyVector2(0.5f, 0.5f));
	title->SetAction(onMouse);
	m_UIManager->AddSprite((int)TEXTURE_ID::TO_TITLE, title);
	m_UIManager->AddSprite((int)TEXTURE_ID::RESULT_TEXT, std::make_shared<Sprite>(TEXTURE_ID::RESULT_TEXT, MyVector2(327, 167), MyVector2(1, 1), MyVector2(0.5f, 0.5f)));


	//�Q�[���̏�Ԃ����Z�b�g
	m_world->GameEnd();
}

void ResultScene::Update(float deltaTime)
{
	m_world->Update(deltaTime);
	if (Mouse::GetInstance().IsPressUp(MouseCommand::LEFT))
	{
		m_UIManager->Collide(Mouse::GetInstance().Position(),
			[&](SpritePtr& sprite)
		{
			if (sprite->TexID() == TEXTURE_ID::RETRY)
			{
				m_isEnd = true;
				m_nextScene = Scene::GamePlay;
			}
			else if(sprite->TexID() == TEXTURE_ID::TO_TITLE)
			{
				m_isEnd = true;
				m_nextScene = Scene::Title;
			}
		});
	}

	m_UIManager->Update(deltaTime);
}

void ResultScene::Draw() const
{
	m_world->Draw();
	m_UIManager->Draw();
}

bool ResultScene::IsEnd() const
{
	return m_isEnd;
}

int ResultScene::Next() const
{
	return (int)m_nextScene;
}

void ResultScene::End()
{
	m_UIManager = nullptr;
	//Up�������ɍH��ɔ������Ă��܂��̂ň�xUpdate������
	Mouse::GetInstance().Update(0.0f);
	m_world->GameReset();
	//�Q�[����ʂɖ߂�ꍇ�A�Đ������s��
	if (m_nextScene == Scene::GamePlay) m_world->StageCreate();
}
