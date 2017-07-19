#pragma once
#include"../CursorState.h"
//���j�b�g�܂ŃJ�[�\���𑀍삷��
class ToUnitState : public CursorState
{
public:
	ToUnitState(LerpCursor* cursor,const UnitPtr& target);
	~ToUnitState();
	void Initialize() override;
	void Update(float deltaTime) override;
	void Draw() const override;
	void End() override;
	int Next() const override;
	bool IsEnd() const override;
};