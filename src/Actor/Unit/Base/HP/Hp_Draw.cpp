#include "Hp_Draw.h"
#include"Actor\Base\IWorld.h"
#include"Loader\Loader.h"
#include<DxLib.h>
#include"UI/Sprite/Sprite.h"
#include"Math/Converter.h"
#include"Base/VectorUtility/VectorUtility.h"
Hp_Draw::Hp_Draw(IWorld& world) :
	m_world(world)
{
	m_spriteManager.Set(TEXTURE_ID::HP_FRAME);
	m_spriteManager.Set(TEXTURE_ID::HP_GAUGE);
}

Hp_Draw::~Hp_Draw()
{
}
void Hp_Draw::Clear()
{
	m_spriteManager.Clear();
}
void Hp_Draw::Set(int maxHP, float hp, const MyVector2& scale, const MyVector3& position)
{
	m_spriteManager.Save(TEXTURE_ID::HP_FRAME, position, scale);

	float percent = hp / (float)maxHP;
	m_spriteManager.Save(TEXTURE_ID::HP_GAUGE, position, scale
		,MyRect(0,0,Loader::GetInstance().TextureSize(TEXTURE_ID::HP_GAUGE).x * percent,
			Loader::GetInstance().TextureSize(TEXTURE_ID::HP_GAUGE).y)
		, Color(2.0f - (percent*2.0f), 2.0f * percent, 0.0f, 1.0f));
}

void Hp_Draw::Draw()
{
	m_spriteManager.Draw();
}
