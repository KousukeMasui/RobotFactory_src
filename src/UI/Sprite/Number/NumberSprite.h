#pragma once
#include"../Sprite.h"
//�����p�摜�N���X
class NumberSprite : public Sprite {
private:
	enum ValueTypeID {
		INT=0,
		FLOAT
	};
public:
	//�R���X�g���N�^
	NumberSprite(const MyVector2& position, const MyVector2& scale, const MyVector2& center,ValueTypeID id);
	//�f�X�g���N�^
	~NumberSprite();
	//���l�ݒ�
	void SetInt(int value);
	void SetFloat(float value);
private:
	ValueTypeID m_valueID;
	int m_valueInt;
	float m_valueFloat;
};