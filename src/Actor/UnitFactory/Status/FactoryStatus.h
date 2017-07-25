#pragma once

//�H��̃X�e�[�^�X�N���X
#include"Actor\Unit\Base\Status/UnitStatus.h"
#include<functional>
#include<map>
#include"../FactoryStatusID.h"
class FactoryStatus
{
public:
	explicit FactoryStatus(const std::function<void(const UnitStatus& status)>& createFunc);
	//�������̃X�e�[�^�X�ɂ��ĕԂ�
	UnitStatus CreateStatus(GameManager* manager) const;
	//�����ɕK�v�Ȏ����������߂ĕԂ�
	int CreatePartsCount() const;

	//�H����܂߂����v�X�e�[�^�X��Ԃ�
	int Total() const;
	//�����\��
	bool IsStatusUp(FactoryStatusID status);
	//�����֐�
	void StatusUp(FactoryStatusID status,GameManager* manager);
public:
	//�H���HP
	int maxHP;
	float hp;
	int healInterval;

	//�X�e�[�^�X�i�[�}�b�v
	std::map<FactoryStatusID, int> status;

	int partsCount;//�ۗL���鎑����
private:
	//���j�b�g�����Ɏg������������ϐ�
	std::function<void(const UnitStatus& status)>createFunc;
};