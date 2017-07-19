#pragma once

#include"../Node/UnitAINode.h"
//�ҋ@��Ԃ̃m�[�h
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