#pragma once

#include"../Node/UnitAINode.h"
//‘Ò‹@ó‘Ô‚Ìƒm[ƒh
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