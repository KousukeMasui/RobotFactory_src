#pragma once
#include"Base/GameUsing.h"
#include<vector>
#include"Math/Vector/MyVector3.h"
//���j�b�g�𕡐������ɓ��������߂̃N���X
class GroupUnits {
public:
	//�R���X�g���N�^
	GroupUnits();
	//�f�X�g���N�^
	~GroupUnits();
	//�ǉ�
	void AddUnit(const UnitPtr& unit);
	//���߂����ۂ̖ړI�n
	void Order(const MyVector3& targetPosition);
	//�X�V
	void Update(float deltaTime);
private:
	//�擪���j�b�g�̑I��
	UnitPtr CheckCaptain();

private:
	//�O���[�v�̃��j�b�g�B
	std::vector<UnitPtr> m_units;
	//���߂̐擪�ɂȂ郆�j�b�g
	UnitPtr m_captainUnit;

	//�ړI�n
	MyVector3 m_targetPosition;
	//�ړ��J�n���邩
	bool m_isMoveStart;
};