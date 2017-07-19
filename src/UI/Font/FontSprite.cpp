#include "FontSprite.h"
#include<DxLib.h>
#include"Loader/Loader.h"

FontSprite::FontSprite(Font_ID fontID, const MyVector2 & position, const std::string& text, const Color & color):
	UI(position,color),
	m_fontID(fontID),
	m_text(text)
{
	m_color = color;
}

FontSprite::~FontSprite()
{
}

void FontSprite::ChangeText(const std::string& text)
{
	m_text = text;
}

std::string FontSprite::GetText() const
{
	return m_text;
}

void FontSprite::Draw() const
{
	DrawStringToHandle(m_position.x, m_position.y, m_text.c_str(),
		DxLib::GetColor(255 * m_color.r, 255 * m_color.g, 255 * m_color.b), Loader::GetInstance().FontHandle(m_fontID));
}
