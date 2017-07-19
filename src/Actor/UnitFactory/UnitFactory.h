#pragma once

#include<string>
#include"Math/Shapes/3D/Ray/Ray.h"
class IWorld;
class Unit;
class UnitStatus;
struct Sphere;
struct Capsule;
struct Line3D;
#include"Math/Collision/HitInfo/HitInfo.h"
#include"Math/Point2/Point2.h"
#include"Status\FactoryStatus.h"
#include"Parameter/FactoryParam.h"
#include"Manager/FactoryManager.h"
#include"Model/Model/Model.h"
#include"AI/AutoAI.h"
#include"Heal/FactoryHeal.h"
class UnitFactory
{
public:
	UnitFactory(IWorld& world, InfluenceID influence,const MyVector3& position,FactoryManager& manager);
	~UnitFactory();

	//���͂̕ύX
	void ChangeInfluence(InfluenceID influence);
	//�񕜂�Ԃ�
	const FactoryHeal& GetHeal() const;


	void Update(float deltaTime);
	//���������ɂ̂ݍs���X�V�֐�
	void NonInfluenceUpdate(float deltaTime);
	void Draw() const;

	bool IsDelete();
	FactoryParam& GetParam();
	bool IsCollide(const MyVector3& position);
	bool IsCollide(const Sphere& other,HitInfo& hit) const;
	bool IsCollide(const Capsule& caspule) const;
	HitInfo IsCollide(const Line3D& line) const;
	void Collide(Unit& other,HitInfo& hit);

	//������u�����͈̔͂ɓ�������true
	bool IsCollide(const Unit& unit);
	void Collide(Unit& unit);
	//��������+����
	void PartsCount(int add);
	int PartsCount() const;//�������̎擾

	FactoryStatus& Status();

	void StatusUp(FactoryStatusID id);
	//�����J�n
	void CreateStart(const UnitStatus& status);
	//��������
	void Create(const UnitStatus& status);

	//�_���[�W�֐�
	void Damage(int attack, InfluenceID influence);

	//�����̎����point��Ԃ�
	std::vector<Point2> GetPoints() const;
	void AddTarget(Point2 target);
	void SubTarget(Point2 target);
	std::vector<Point2> GetTargeted() const;

	//�����̍H���node��2��S�Ď擾����
	std::vector<Point2> MyPoints() const;

	void SelectUnit(const UnitPtr& unit);
	const UnitPtrs GetAutoUnits() const;
	void Heal(float power);//�񕜊֐�
private:

	//�����point�����߂�
	void PointsSet();

private:
	IWorld& m_world;
	FactoryManager& m_manager;
	StaticModel m_model;
	Point2 m_point;
	//�������郆�j�b�g�̃X�e�[�^�X
	FactoryStatus m_status;

	FactoryParam m_param;
	//�����point
	std::vector<Point2> m_circlePoints;
	//�����point
	std::vector<Point2> m_myPoints;
	//���݁A�G�l�~�[�̃��j�b�g���_���Ă���Point�z��
	std::vector<Point2> m_targetedPoints;


	FactoryHeal m_heal;

	AutoAI m_autoAI;
	//�������郆�j�b�g�̃X�e�[�^�X
	std::list<UnitStatus> m_createStatus;
};