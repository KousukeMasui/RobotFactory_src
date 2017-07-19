#pragma once
#include"../Sprite/Sprite.h"
#include"../Sprite/Base/SpritePtr.h"
#include"../Font/FontSprite.h"
#include"Base/Manager/TemplateManager.h"
#include"Math/Vector/MyVector2.h"
//sprite��font���i�[���Č��������s����悤�ɂ����Ǘ��N���X
class UIManager
{
public:
	UIManager();
	~UIManager();
	//�������֐�
	void Clear();
	//�ǉ��֐�
	void AddSprite(int id, const SpritePtr& sprite);
	void AddText(int id, const std::shared_ptr<FontSprite>& text);
	//�폜�֐�
	void DeleteSprite(int id);
	void DeleteText(int id);
	//�����֐�
	SpritePtr FindSprite(int id);
	const SpritePtr FindSprite(int id) const;
	std::shared_ptr<FontSprite> FindText(int id);
	//�摜�����蔻��֐�
	void Collide(const MyVector2& position, std::function<void(SpritePtr& sprite)> collideFunc);
	//�X�V
	void Update(float deltaTime);
	//�`��
	void Draw() const;
private:
	TemplateManager<int, FontSprite, int> m_fontManager;
	TemplateManager<int, Sprite, int> m_spriteManager;
};