#pragma once
#include"Tree\TreeNode.h"
class Unit;
enum class UnitNodeID;
//AI用に継承させるノード
class UnitAINode : public TreeNode
{
public:
	explicit UnitAINode(Unit& param, UnitNodeID nodeID);
	~UnitAINode();

	void Update(float deltaTime) override;

private:
	virtual void OnUpdate(float deltaTime) = 0;//子クラスの更新処理
	virtual bool SetIsEnd() =0;//m_isEndをtrueにする計算を返す関数
protected:
	Unit& m_unit;
};