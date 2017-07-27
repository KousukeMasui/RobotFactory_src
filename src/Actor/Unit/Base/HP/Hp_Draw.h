#pragma once
//HPバーの表示クラス
#include"Model/Model/Model.h"
#include"Math\Color\Color.h"
#include"Math/Vector/MyVector2.h"
#include"UI/Sprite/Base/SpritePtr.h"
#include<vector>
#include"UI/Sprite/Base/WorldToSpriteManager.h"
class IWorld;
class UnitParameter;
class Hp_Draw
{
private:
	struct SpriteParameter {
		SpriteParameter(const MyVector2& position, const MyVector2& scale,float hpPercent,float zBuffer) :
			position(position), scale(scale),hpPercent(hpPercent),zBuffer(zBuffer) {}
		MyVector2 position;
		MyVector2 scale;
		float hpPercent;
		float zBuffer;
	};
public:
	explicit Hp_Draw(IWorld& world);
	~Hp_Draw();
	void Clear();
	void Set(float maxHP,float hp,const MyVector2& scale,const MyVector3& position);

	void Draw();
private:
	IWorld& m_world;

	WorldToSpriteManager m_spriteManager;
};