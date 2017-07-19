#pragma once

#include"../Node/UnitAINode.h"
class IWorld;
//‚Á‚Ä‚¢‚éê‡‚Ì‘Ò‹@ƒm[ƒh
class LiftIdleNode : public UnitAINode
{
public:
	LiftIdleNode(IWorld& world, Unit& unit);
	~LiftIdleNode();

	void Start() override;
	void End() override;

	virtual bool Branch()override;
private:
	void OnUpdate(float deltaTime) override;
	bool SetIsEnd() override;

private:
	IWorld& m_world;
};