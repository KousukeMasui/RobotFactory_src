#pragma once

//持ち上げノード 攻撃の一つ下の位置

#include"../Node/UnitAINode.h"
#include"Base/GameUsing.h"
#include"Math/Vector/MyVector3.h"
class LiftObject;
class IWorld;
//待機状態のノード
class LiftUpNode : public UnitAINode
{
public:
	LiftUpNode(IWorld& world, Unit& unit);
	~LiftUpNode();

	void Start() override;
	void End() override;

	virtual bool Branch()override;
	
private:
	void OnUpdate(float deltaTime) override;
	bool SetIsEnd() override;
private:
	IWorld& m_world;

};