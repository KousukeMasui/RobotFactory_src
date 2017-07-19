#include "NumberSprite.h"

NumberSprite::NumberSprite(const MyVector2 & position, const MyVector2 & scale, const MyVector2 & center, ValueTypeID id):
	Sprite(TEXTURE_ID::NUMBER,position,scale,center),
	m_valueID(id),
	m_valueInt(0),
	m_valueFloat(0.0f)
{
}

NumberSprite::~NumberSprite()
{
}

void NumberSprite::SetInt(int value)
{
}

void NumberSprite::SetFloat(float value)
{
}
