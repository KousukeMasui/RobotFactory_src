#pragma once

//�H��̃X�e�[�^�X�N���X
#include"Actor\Unit\Base\Status/UnitStatus.h"
#include<functional>
#include<map>
#include"../FactoryStatusID.h"
class CSVData;
class FactoryStatus
{
public:
	explicit FactoryStatus(CSVData& csvData,const std::function<void(const UnitStatus& status)>& createFunc);
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
	float maxHP;
	float hp;
	int healInterval;

	//�X�e�[�^�X�i�[�}�b�v
	std::map<FactoryStatusID, int> status;

	int partsCount;//�ۗL���鎑����
private:
	//���j�b�g�����Ɏg������������ϐ�
	std::function<void(const UnitStatus& status)>createFunc;
};