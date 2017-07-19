#pragma once
#include<memory>
#include"../LiftObject/LiftObject.h"
#include"../Influence/InfluenceID.h"
#include"Tree/Tree.h"
#include"Base/Status/UnitStatus.h"
#include"Effect/EffectPtr.h"
#include"Math/Shapes/3D/Capsule/Capsule.h"
#include"Model/AnimationModel/AnimationModel.h"
#include<functional>
class IWorld;
//��ʏ�ɖ��߂��o�����ۂɓ����L�����N�^�[
//�����ς��Ƃ��͈��p�����[�^���擾���Ă�����E���čĐ�������
class Unit : public LiftObject
{
public:
	Unit(IWorld& world, InfluenceID influence,const MyVector3& position,const UnitStatus& status);
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

	//�o�H�폜
	void RoadDelete();
	//�X�V
	void Update(float deltaTime);
	//�ړ��ݒ�
	void Move(const MyVector3& velocity);
	//Manager�ݒ�֐�
	Unit& GetParam();
	//���݈ړ�����
	bool IsMove() const;
	//�^��ł���I�u�W�F�N�g��Ԃ�
	LiftObject* GetLift();
	//�ړ�������Ԃ�
	MyVector3 GetVelocity() const;
	//�A�j���[�V�������f����Ԃ�
	AnimationModel& GetModel();

	//��]�@�ړ����������� ��]���I�������true
	bool LerpToVelocity(const MyVector3& velocity);

	MyVector3 ToNextVelocity() const;
	//�ړI�n��Ԃ�
	MyVector3 Target() const;
private:
	//��
	void Heal(float value);
	//�o�H�T���p���b�Z�[�W
	void RootMessage(int messageID, void* data);
	//�ړ�������ݒ肷��
	void SetVelocity();
private:
	IWorld& m_world;
	//�ړI�n�܂ł̓�
	std::vector<MyVector3> m_roadPositions;

	bool m_isDelete;
	//�r�w�C�r�A�c���[
	Tree m_AITree;
	//���݂̃m�[�hID
	int m_nodeID;
	//�A�j���[�V�����p���f��
	AnimationModel m_model;
	//�����蔻��p�}�`
	Sphere m_sphere;
	Capsule m_capsule;
	//����
	InfluenceID m_influence;
	//�H��ɂ���ĕς��X�e�[�^�X
	UnitStatus m_status;
	//�^��ł��镨��
	std::shared_ptr<LiftObject> m_liftObject;
	//�ړ���
	MyVector3 m_velocity;
	//��~�����s�֐�
	std::function<void()> m_stopFunc;
};