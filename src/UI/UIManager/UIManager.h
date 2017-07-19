#pragma once
#include"../Sprite/Sprite.h"
#include"../Sprite/Base/SpritePtr.h"
#include"../Font/FontSprite.h"
#include"Base/Manager/TemplateManager.h"
#include"Math/Vector/MyVector2.h"
//spriteとfontを格納して検索等を行えるようにした管理クラス
class UIManager
{
public:
	UIManager();
	~UIManager();
	//初期化関数
	void Clear();
	//追加関数
	void AddSprite(int id, const SpritePtr& sprite);
	void AddText(int id, const std::shared_ptr<FontSprite>& text);
	//削除関数
	void DeleteSprite(int id);
	void DeleteText(int id);
	//検索関数
	SpritePtr FindSprite(int id);
	const SpritePtr FindSprite(int id) const;
	std::shared_ptr<FontSprite> FindText(int id);
	//画像当たり判定関数
	void Collide(const MyVector2& position, std::function<void(SpritePtr& sprite)> collideFunc);
	//更新
	void Update(float deltaTime);
	//描画
	void Draw() const;
private:
	TemplateManager<int, FontSprite, int> m_fontManager;
	TemplateManager<int, Sprite, int> m_spriteManager;
};