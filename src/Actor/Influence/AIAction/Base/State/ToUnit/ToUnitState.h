#pragma once
#include"../CursorState.h"
//ユニットまでカーソルを操作する
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