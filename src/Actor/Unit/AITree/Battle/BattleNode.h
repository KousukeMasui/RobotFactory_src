#pragma once

#include"../Node/UnitAINode.h"
class IWorld;
#include"Math/Matrix/MyMatrix4.h"
#include"Base/GameUsing.h"
//ë“ã@èÛë‘ÇÃÉmÅ[Éh
class BattleNode : public UnitAINode
{
public:
	BattleNode(IWorld& world,Unit& param);
	~BattleNode();
	void Start() override;
	void End() override;
	virtual bool Branch()override;
private:
	void OnUpdate(float deltaTime) override;
	bool SetIsEnd() override;
private:
	IWorld& m_world;

	UnitPtr m_target;
	FactoryPtr m_targetFactory;
	
};