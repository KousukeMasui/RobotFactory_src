#pragma once

#include"../Node/UnitAINode.h"
#include"Base/GameUsing.h"
class IWorld;
//待機状態のノード
class IdleNode : public UnitAINode
{
public:
	IdleNode(IWorld& world, Unit& unit);
	~IdleNode();

	void Start() override;
	void End() override;

	virtual bool Branch()override;

private:
	void OnUpdate(float deltaTime) override;
	bool SetIsEnd() override;
};