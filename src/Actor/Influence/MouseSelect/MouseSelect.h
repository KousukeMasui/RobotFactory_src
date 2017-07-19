#pragma once
#include"Cursor/SelectCursor.h"
#include"Base/GameUsing.h"
class IWorld;
struct Line3D;
//マウスでユニットを選択するクラス AutoState,Playerにて使用予定
class MouseSelect
{
public:
	explicit MouseSelect(IWorld& world);
	~MouseSelect();

	UnitPtr Update(float deltaTime);

	SelectCursor& GetCursor();
	void Draw() const;
private:
	MyVector3 CursorPosition(const Line3D & line, HitInfo & hit) const;
private:
	IWorld& m_world;
	SelectCursor m_cursor;
};