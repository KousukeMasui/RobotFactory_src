#pragma once
#include"Resources.h"
#include<map>
#include<vector>
#include"Math/Vector/MyVector3.h"
#include"Math/Vector/MyVector2.h"
#include"Math/Color/Color.h"
#include"Math/MyRect/MyRect.h"
#include"UI/Sprite/Base/SpritePtr.h"
//ワールド座標からスクリーン座標に変換して画像描画を行うクラス
class WorldToSpriteManager {
private:
	//描画に必要なステータス
	struct SpriteParam {
		SpriteParam(TEXTURE_ID id,const MyVector2& position, const MyVector2& scale, float z, MyRect rect, Color color);
		TEXTURE_ID id;
		MyVector2 position;
		MyVector2 scale;
		float z;//スクリーン座標にした際のカメラとの距離(+-あり)
		MyRect rect;
		Color color;
	};
public:
	WorldToSpriteManager();
	~WorldToSpriteManager();
	//初期化関数 Spriteを複数生成するのを防止するために作成
	void Set(TEXTURE_ID id);

	//位置を保存する 画像の重なりを防止するために一度変数に格納して使用する
	void Save(TEXTURE_ID id, const MyVector3& position, const MyVector2& size);
	//rect登録版位置保存
	void Save(TEXTURE_ID id, const MyVector3& position, const MyVector2& size,const MyRect& rect,const Color& color = Color::White);

	//描画
	void Draw() const;
	//初期化
	void Clear();
private:
	//描画可能な位置にいるか
	bool IsDraw(const MyVector3& position,MyVector3& screenPos);
private:
	std::vector<std::shared_ptr<SpriteParam>> m_spriteParams;
	std::map<TEXTURE_ID, SpritePtr> m_spriteMap;
};