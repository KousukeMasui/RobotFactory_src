#pragma once

#include"Base/GameUsing.h"
#include<map>
#include<functional>
class GameManager;
class MyVector3;
class Object;
//�����v�Z���A���������������񓮂��̂��f�[�^�����đj�~����
class MetaDistance
{
public:
	//�R���X�g���N�^
	MetaDistance();
	//�f�X�g���N�^
	~MetaDistance();
	//�J�n
	void Start(GameManager* manager);
	//������
	void Clear();

	//���͐����t��
	UnitPtr GetNearUnitOtherInfluence(const Unit& unit,const std::function<bool(const Unit& unit)>& searchFunc = nullptr);
	UnitPtr GetNearUnitInfluence(const Unit& unit, const std::function<bool(const Unit& unit)>& searchFunc = nullptr);
	//��ԋ߂����j�b�g���擾
	UnitPtr GetNearUnit(const Object& obj);

	//��ԋ߂����Ă�I�u�W�F�N�g��Ԃ�
	LiftObjectPtr GetNearLift(const Unit& unit,const std::function<bool(const LiftObject& lift)>& searchFunc = nullptr);
	//������Ԃ�
	float Distance(const Object& o1, const Object& o2);
	//������Ԃ�
	float Distance(const LiftObject& l, UnitFactory* f);
	//��ԋ߂����j�b�g��Ԃ�
	UnitPtr NearUnit(const Object& obj, const UnitPtrs& units);
	//��ԋ߂��H���Ԃ�
	FactoryPtr NearFactory(const Object& obj, const FactoryPtrs& factorys);
private:
	//��ԋ߂����Ă�I�u�W�F�N�g��Ԃ�
	LiftObjectPtr NearLeft(const Unit& unit,const LiftObjects& lifts);
	//�����v�Z
	float DistanceCalc(const Object& o1, const Object& o2);
	float DistanceCalc(const LiftObject& l, UnitFactory* f);
	//���̃t���[�����Ɍ������Ă��邩
	bool IsFindThisFrame(void* v1,void* v2);

	float GetDistance(void* d1, void* d2);
private:
	GameManager* m_manager;
	//�����ۑ��ϐ�
	std::map<void*, std::map<void*, float>> m_distanceData;
};