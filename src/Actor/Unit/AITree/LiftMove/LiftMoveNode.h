#pragma once

#include"../Node/UnitAINode.h"
//ë“ã@èÛë‘ÇÃÉmÅ[Éh
class LiftMoveNode : public UnitAINode
{
public:
	explicit LiftMoveNode(Unit& unit);
	~LiftMoveNode();

	void Start() override;
	void End() override;

	virtual bool Branch()override;
private:
	void OnUpdate(float deltaTime) override;
	bool SetIsEnd() override;

private:
};