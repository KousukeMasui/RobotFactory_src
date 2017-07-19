#pragma once
#include"../CursorState.h"
class IWorld;
#include"Base/GameUsing.h"
//���j�b�g������or���j�b�g�܂ňړ����閽�߂��o��
class OrderLiftObjectState : public CursorState
{
public:
	OrderLiftObjectState(IWorld& world,LerpCursor* cursor,const UnitPtr& orderUnit,const LiftObjectPtr& lift);
	~OrderLiftObjectState();
	void Initialize() override;
	void Update(float deltaTime) override;
	void Draw() const override;
	void End() override;
	int Next() const override;
	bool IsEnd() const override;
private:
	IWorld& m_world;
	std::shared_ptr<LiftObject> m_lift;
};