#pragma once
#include"UI/UI.h"
#include"Math/MyRect/MyRect.h"
#include"Resources.h"
//2Dテクスチャ描画クラス
class Sprite: public UI
{
public:
	//デフォルトコンストラクタ
	Sprite();
	//コンストラクタ
	Sprite(TEXTURE_ID id,MyVector2 position,MyVector2 scale,MyVector2 center);
	//デストラクタ
	~Sprite();
	//描画
	void Draw() const override;
	//拡大率
	void Scale(const MyVector2& scale);
	MyVector2 Scale() const;
	//回転の中心位置
	void Center(const MyVector2& center);
	MyVector2 Center() const;
	//画像の切り取り位置
	void Rect(const MyRect& rect);
	MyRect Rect() const;
	//回転角度
	void Rad(const float& rad);
	float Rad() const;
	//テクスチャの大きさ
	MyVector2 TexSize() const;
	//テクスチャのID
	TEXTURE_ID TexID() const;
	//当たり判定
	bool IsCollide(const MyVector2& position) const;
private:
	//解像度が変更されても描画レイアウトを変更しないための関数
	MyVector2 SetScreenSizeScale(const MyVector2 & scale) const;
private:
	TEXTURE_ID m_texID;
protected:
	MyVector2 m_scale;
	MyVector2 m_center;
	MyRect m_rect;
	float m_rad;
	//スケールをかけない本来の大きさ
	MyVector2 m_texSize;

	MyVector2 m_drawScale;

};