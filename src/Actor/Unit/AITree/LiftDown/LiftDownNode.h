#pragma once

#include"../Node/UnitAINode.h"
class IWorld;
class UnitFactory;
#include"Base/GameUsing.h"
//ï®ÇíuÇ≠ÉmÅ[Éh
class LiftDownNode : public UnitAINode
{
public:
	LiftDownNode(IWorld& world, Unit& unit);
	~LiftDownNode();

	void Start() override;
	void End() override;

	virtual bool Branch()override;

private:
	void OnUpdate(float deltaTime) override;
	bool SetIsEnd() override;
private:
	IWorld& m_world;
	FactoryPtr m_factory;
};