#pragma once

//�H��̃X�e�[�^�X�N���X
#include"Actor\Unit\Base\Status/UnitStatus.h"
#include<functional>
#include<map>
#include"../FactoryStatusID.h"
#include"Create/UnitCreate.h"
class CSVData;
class IWorld;
class RootFind;
struct FactoryParam;
class FactoryStatus
{
public:
	explicit FactoryStatus(IWorld& world,RootFind& find,FactoryParam& param);
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

	void Create(const UnitStatus& status);
public:
	//�H���HP
	float maxHP;
	float hp;
	int healInterval;

	//�X�e�[�^�X�i�[�}�b�v
	std::map<FactoryStatusID, int> status;

	int partsCount;//�ۗL���鎑����
private:
	UnitCreate m_create;
};