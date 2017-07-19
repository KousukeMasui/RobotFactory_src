#pragma once


//���j�b�g�̃Q�[����Ԃŕω�����X�e�[�^�X
class UnitStatus
{
public:
	UnitStatus(int factoryMaxHP = 0, float hp = 0.0f, int attack = 0, int speed = 0,float range = 0.0f);

	//���݂�HP�̃p�[�Z���g��1~0�ŕԂ�
	float hpPercent() const;
	//���ۂ̈ړ����x��Ԃ�
	float MoveSpeed() const;
	int factoryMaxHP;	//�̗͂̏�� �H��p�ϐ��@maxHP�͂�������Ɍv�Z����
	int maxHP;	//�̗͂̏��
	float hp;		//���݂̗̑�
	int attack;	//�U����
	int speed;	//�ړ����x
	float range;
};

UnitStatus operator +(const UnitStatus& s1, const UnitStatus& s2);
UnitStatus operator +=(UnitStatus& s1, const UnitStatus& s2);
UnitStatus operator -(const UnitStatus& s1, const UnitStatus& s2);
UnitStatus operator -=(UnitStatus& s1, const UnitStatus& s2);
bool operator ==(const UnitStatus& s1, const UnitStatus& s2);
bool operator !=(const UnitStatus& s1, const UnitStatus& s2);