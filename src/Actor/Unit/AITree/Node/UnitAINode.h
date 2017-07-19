#pragma once
#include"Tree\TreeNode.h"
class Unit;
enum class UnitNodeID;
//AI�p�Ɍp��������m�[�h
class UnitAINode : public TreeNode
{
public:
	explicit UnitAINode(Unit& param, UnitNodeID nodeID);
	~UnitAINode();

	void Update(float deltaTime) override;

private:
	virtual void OnUpdate(float deltaTime) = 0;//�q�N���X�̍X�V����
	virtual bool SetIsEnd() =0;//m_isEnd��true�ɂ���v�Z��Ԃ��֐�
protected:
	Unit& m_unit;
};