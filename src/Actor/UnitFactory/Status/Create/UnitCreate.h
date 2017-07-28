#pragma once
class Unit;
class UnitStatus;
class IWorld;
struct FactoryParam;
class RootFind;
#include"Math/Vector/MyVector3.h"
#include"Math/Shapes/3D/Sphere/Sphere.h"
#include"Base/GameUsing.h"
#include<list>
class UnitCreate {
public:
	//�R���X�g���N�^
	UnitCreate(IWorld& world,RootFind& find,FactoryParam& param);
	//�f�X�g���N�^
	~UnitCreate();
	//�X�V
	void Update();
	//�����蔻��@�����ɐG��Ă��郆�j�b�g�������琶���ł��Ȃ�����
	bool IsCollide();
	//��������
	void Create(const UnitStatus& status);
private:
	//���ۂ̐�������
	void Create();
private:
	IWorld& m_world;
	//���̓����蔻��
	Sphere m_sphere;
	//�������郆�j�b�g�̃X�e�[�^�X
	std::list<UnitStatus> m_status;
	FactoryParam& m_param;
	RootFind& m_find;
	UnitPtr m_createUnit;
};