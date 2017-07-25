#pragma once
#include"Base/GameUsing.h"
#include"Math/Vector/MyVector3.h"
class GameManager;
//���j�b�g��Ǐ]������
//�G�ƃv���C���[���j�b�g�̈ړ��ŏ����ύX����̂Ōp���Ŏ���
class ToUnit {
public:
	ToUnit(GameManager& manager,Unit& unit);
	~ToUnit();

	//�ړI���j�b�g��ݒ�
	void SetTarget(const UnitPtr& target);
	//�X�V
	void Update();
private:
	//�ړI���j�b�g�܂ňړ�����o�H���v�Z
	void ToUnitRoot();
private:
	//�����̃��j�b�g
	Unit& m_myUnit;
	//�}�l�[�W��
	GameManager& m_manager;
	//�ǂꂭ�炢�ړ����ꂽ��ēx�v�Z���邩
	const float m_moveDistance;
	//�Ǐ]���郆�j�b�g
	UnitPtr m_targetUnit;
	//�Ǐ]���郆�j�b�g�̑O�̈ʒu
	MyVector3 m_prevPosition;
};