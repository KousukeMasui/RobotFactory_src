#pragma once
class IWorld;
#include<forward_list>
#include"Base/GameUsing.h"
#include"../InfluenceID.h"
//Player,Enemy�̐e�N���X
class Influence
{
public:
	Influence(IWorld& world, InfluenceID id);
	~Influence();
	//���R���j�b�g��S�Ď擾
	UnitPtrs GetUnits();
	virtual void Update(float deltaTime) = 0;
	virtual void Draw() const = 0;
	//���݂͍폜�\��͖����̂�false��Ԃ�
	bool IsDelete() { return false; }
protected:
	IWorld& m_world;
	const InfluenceID m_influenceID;
};