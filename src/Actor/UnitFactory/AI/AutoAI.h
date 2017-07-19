#pragma once
#include"Base/GameUsing.h"
#include"Base/AI/Priority/Shaft/Shaft.h"
#include"Cursor/LerpCursor.h"
#include"UI/Sprite/Base/WorldToSpriteManager.h"
class UnitFactory;
//UnitÇÉIÅ[ÉgëÄçÏÇ∑ÇÈAI
class AutoAI
{
public:
	AutoAI(IWorld& world,const MyVector3& position, UnitFactory& factory);
	~AutoAI();
	void Select(const UnitPtr& unit);

	void Update(float deltaTime);
	void Draw() const;

	const UnitPtrs GetUnits() const;
private:
	void Add(const UnitPtr& unit);
	void Sub(const UnitPtr& unit);
private:
	Shaft m_shaft;
	LerpCursor m_cursor;
	UnitPtrs m_units;
	WorldToSpriteManager m_worldSpriteManager;
};