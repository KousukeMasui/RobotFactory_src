#include "UIManager.h"
#include"../Sprite/Sprite.h"
UIManager::UIManager()
{
}

UIManager::~UIManager()
{
}

void UIManager::Clear()
{
	m_spriteManager.Delete();
	m_fontManager.Delete();
}

void UIManager::AddSprite(int id, const SpritePtr & sprite)
{
	m_spriteManager.Add(id, sprite);
}

void UIManager::AddText(int id, const std::shared_ptr<FontSprite>& text)
{
	m_fontManager.Add(id, text);
}

void UIManager::DeleteSprite(int id)
{
	m_spriteManager.Delete(id);
}

void UIManager::DeleteText(int id)
{
	m_fontManager.Delete(id);
}

SpritePtr UIManager::FindSprite(int id)
{
	return m_spriteManager.GetVector(id).front();
}

const SpritePtr UIManager::FindSprite(int id) const
{
	return m_spriteManager.GetVector(id).front();
}

std::shared_ptr<FontSprite> UIManager::FindText(int id)
{
	return m_fontManager.GetVector(id).front();
}

void UIManager::Collide(const MyVector2 & position, std::function<void(SpritePtr& sprite)> collideFunc)
{
	m_spriteManager.Function([&](SpritePtr sprite) {
		if (sprite->IsCollide(position))
		{
			collideFunc(sprite);
		}
	});
}

void UIManager::Update(float deltaTime)
{
	m_spriteManager.Update(deltaTime);
	m_fontManager.Update(deltaTime);
}

void UIManager::Draw() const
{
	m_spriteManager.Draw();
	m_fontManager.Draw();
}
