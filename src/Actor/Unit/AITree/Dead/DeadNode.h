#pragma once

#include"../Node/UnitAINode.h"
class IWorld;
//待機状態のノード
class DeadNode : public UnitAINode
{
public:
	DeadNode(IWorld& world, Unit& param);
	~DeadNode();

	void Start() override;
	void End() override;

	virtual bool Branch()override;
private:
	void OnUpdate(float deltaTime) override;
	bool SetIsEnd() override;

private:
	IWorld& m_world;
};