#pragma once

#include<map>
	enum class UNIT_STATUS_ID {
		HP = 0,
		ATK,
		SPD,
		RANGE,
		MAX_HP
	};
class GameManager;
//���j�b�g�̃Q�[����Ԃŕω�����X�e�[�^�X
class UnitStatus
{
public:
	UnitStatus(int hpLevel = 0, int attackLevel = 0, int speedLevel = 0, float range = 0.0f, GameManager* manager = nullptr);

	//���݂�HP�̃p�[�Z���g��1~0�ŕԂ�
	float hpPercent() const;

	int Level(UNIT_STATUS_ID id) const;
	float Status(UNIT_STATUS_ID id) const;

	void AddHP(float hp);
private:
	//�H��̃X�e�[�^�X���󂯎��
	std::map<UNIT_STATUS_ID, int> m_levels;
	//�Q�[����̎��ۂ̃X�e�[�^�X
	std::map<UNIT_STATUS_ID, float> m_status;
};

UnitStatus operator +(const UnitStatus& s1, const UnitStatus& s2);
UnitStatus operator +=(UnitStatus& s1, const UnitStatus& s2);
UnitStatus operator -(const UnitStatus& s1, const UnitStatus& s2);
UnitStatus operator -=(UnitStatus& s1, const UnitStatus& s2);