#pragma once
#include"../Sprite.h"
//数字用画像クラス
class NumberSprite : public Sprite {
private:
	enum ValueTypeID {
		INT=0,
		FLOAT
	};
public:
	//コンストラクタ
	NumberSprite(const MyVector2& position, const MyVector2& scale, const MyVector2& center,ValueTypeID id);
	//デストラクタ
	~NumberSprite();
	//数値設定
	void SetInt(int value);
	void SetFloat(float value);
private:
	ValueTypeID m_valueID;
	int m_valueInt;
	float m_valueFloat;
};