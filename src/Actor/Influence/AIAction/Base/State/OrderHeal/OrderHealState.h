#pragma once
#include"../CursorState.h"
class IWorld;
#include"Base/GameUsing.h"
#include"Math/Shapes/3D/Line/Line3D.h"
//���j�b�g������or���j�b�g�܂ňړ����閽�߂��o��
class OrderHealState : public CursorState
{
public:
	OrderHealState(IWorld& world, LerpCursor* cursor, const UnitPtr& orderUnit,UnitFactory* factory);
	~OrderHealState();
	void Initialize() override;
	void Update(float deltaTime) override;
	void Draw() const override;
	void End() override;
	int Next() const override;
	bool IsEnd() const override;
private:
	IWorld& m_world;
	UnitFactory* m_factory;
	MyVector3 m_targetPosition;
	Line3D m_line;
};