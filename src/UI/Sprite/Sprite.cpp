#include "Sprite.h"

#include<DxLib.h>
#include"Loader/Loader.h"
#include"Screen/Screen.h"
Sprite::Sprite():UI(MyVector2(), Color::White){
}
Sprite::Sprite(TEXTURE_ID id,MyVector2 position, MyVector2 scale, MyVector2 center) :
	UI(position,Color::White),
	m_texID(id),
	m_scale(scale),
	m_center(center),
	m_texSize(),
	m_rad(0.0f),
	m_rect(),
	m_drawScale(SetScreenSizeScale(scale))
{
	m_texSize = Loader::GetInstance().TextureSize(id);

	m_rect = MyRect(0, 0, m_texSize.x, m_texSize.y);
}

Sprite::~Sprite()
{
}

void Sprite::Draw() const
{
	int a = (int) (255.0f * m_color.a);
	SetDrawBlendMode(DX_BLENDMODE_ALPHA, a);
	SetDrawBright(255.0f*m_color.r, 255.0f*m_color.g, 255.0f*m_color.b);
	DrawRectRotaGraph3F(
		m_drawPos.x, m_drawPos.y, m_rect.left, m_rect.top, m_rect.right, m_rect.bottom, 
		m_center.x, m_center.y, m_drawScale.x, m_drawScale.y, m_rad, Loader::GetInstance().TextureHandle(m_texID), true, false);

	SetDrawBright(255,255,255);
	SetDrawBlendMode(DX_BLENDMODE_ALPHA, 255);

	for (auto child : m_children)
		child->Draw();
}


void Sprite::Scale(const MyVector2 & scale)
{
	m_scale = scale;
	m_drawScale = SetScreenSizeScale(scale);
}

MyVector2 Sprite::Scale() const
{
	return m_scale;
}

void Sprite::Center(const MyVector2 & center)
{
	this->m_center = center;
}

MyVector2 Sprite::Center() const
{
	return m_center;
}

void Sprite::Rect(const MyRect & rect)
{
	this->m_rect = rect;
}

MyRect Sprite::Rect() const
{
	return m_rect;
}

void Sprite::Rad(const float & rad)
{
	this->m_rad = rad;
}

float Sprite::Rad() const
{
	return m_rad;
}

MyVector2 Sprite::TexSize() const
{
	return m_texSize;
}

TEXTURE_ID Sprite::TexID() const
{
	return m_texID;
}

bool Sprite::IsCollide(const MyVector2 & position) const
{
	return MyVector2::Inside(position, m_position, m_position + MyVector2(m_texSize.x * m_scale.x, m_texSize.y * m_scale.y));
}
MyVector2 Sprite::SetScreenSizeScale(const MyVector2 & scale) const
{
	return MyVector2(scale.x * Screen::RESOLUTION.x / Screen::SCREEN_SIZE.x, scale.y*Screen::RESOLUTION.y / Screen::SCREEN_SIZE.y);
}
