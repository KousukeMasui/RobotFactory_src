#pragma once
#include<memory>
#include"../LiftObject/LiftObject.h"
#include"../Influence/InfluenceID.h"
#include"Base/Manager/Tree/Tree.h"
#include"Base/Status/UnitStatus.h"
#include"Effect/EffectPtr.h"
#include"Math/Shapes/3D/Capsule/Capsule.h"
#include"Model/AnimationModel/AnimationModel.h"
#include"ToUnit/ToUnit.h"
#include<functional>
#include"MetaAI/RootFind/RootAgent.h"
class IWorld;
//��ʏ�ɖ��߂��o�����ۂɓ����L�����N�^�[
//�����ς��Ƃ��͈��p�����[�^���擾���Ă�����E���čĐ�������
class Unit : public LiftObject
{
public:
	Unit(IWorld& world,RootFind& find, InfluenceID influence,const MyVector3& position,const UnitStatus& status);
	~Unit();
	//�������ꂽ�ۂ̏���
	void CreateAI(const std::function<void()>& createFunc);
	//�X�e�[�^�X��Ԃ�
	UnitStatus& GetStatus();
	//�v���C���[�̑I�𓖂��蔻��
	bool IsCollide(const Line3D& line);
	//���݂̃r�w�C�r�A��ID��Ԃ�
	int NodeID() const;
	//�`��
	void Draw() const;
	//���͂�Ԃ�
	InfluenceID GetInfluence() const;
	//���b�Z�[�W���󂯎��
	void Message(int messageID,void* data) override;
	//�폜���邩
	bool IsDelete() const override;
	//����ł��邩
	bool IsDead() const;
	//�H��ɒu���ꂽ�ۂ̏���
	void LiftDown(FactoryPtr factory) override;
	//���j�b�g�Ƃ̓����蔻��
	bool IsCollide(const Unit& other);
	//���������ꍇ�̏���
	void Collide(Unit& other);
	//�����蔻��p�}�`��Ԃ�
	Sphere GetSphere() const override;
	//�X�V
	void Update(float deltaTime);
	//�ړ��ݒ�
	void Move(const MyVector3& velocity);
	//Manager�ݒ�֐�
	Unit& GetParam();
	//�^��ł���I�u�W�F�N�g��Ԃ�
	LiftObject* GetLift();
	//�A�j���[�V�������f����Ԃ�
	AnimationModel& GetModel();

	RootAgent& Agent();
	//�����w��̉�]����
	bool RotateVelocity(const MyVector3& velocity,float deltaTime);
private:
	//��
	void Heal(float value);
private:
	IWorld& m_world;
	//�폜���邩
	bool m_isDelete;
	//�r�w�C�r�A�c���[
	Tree m_AITree;
	//���݂̃m�[�hID
	int m_nodeID;
	//�A�j���[�V�����p���f��
	AnimationModel m_model;
	Capsule m_capsule;
	//����
	InfluenceID m_influence;
	//�H��ɂ���ĕς��X�e�[�^�X
	UnitStatus m_status;
	//�^��ł��镨��
	std::shared_ptr<LiftObject> m_liftObject;
	//��~�����s�֐�
	std::function<void()> m_stopFunc;
	//���j�b�g�Ǐ]�N���X
	ToUnit m_toUnit;

	//�o�H�T��
	RootAgent m_rootAgent;
};