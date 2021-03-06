#pragma once

#include"../Node/UnitAINode.h"
//待機状態のノード
class MoveNode : public UnitAINode
{
public:
	explicit MoveNode(Unit& unit);
	~MoveNode();

	void Start() override;
	void End() override;

	virtual bool Branch()override;
private:
	void OnUpdate(float deltaTime) override;
	bool SetIsEnd() override;

};