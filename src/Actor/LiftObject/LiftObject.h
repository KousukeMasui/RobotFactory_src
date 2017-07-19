#pragma once
#include"Object\Object.h"
class Unit;
#include"Base/GameUsing.h"
#include"Math/Shapes/3D/Sphere/Sphere.h"
enum class LIFT_ID
{
	UNIT,
	PARTS
};
//�����グ����I�u�W�F�N�g�̐e�N���X
class LiftObject : public Object
{
public:
	LiftObject(LIFT_ID id,const MyVector3& position);
	~LiftObject();

	void LiftStart();
	void LiftEnd();
	//�����グ����֐�
	void LiftUp(Unit& unit);
	//���낵���ۂ̏���
	virtual void LiftDown(FactoryPtr factory) = 0;
	void LiftUpEnd();
	bool IsLiftStart() const;//�����n�߂�ꂽ��true
	bool IsLiftEnd() const;//�����I�������

	LIFT_ID GetID() const;

	virtual bool IsDelete() const = 0;

	virtual Sphere GetSphere() const = 0;
private:
	LIFT_ID m_id;
protected:
	bool m_isLifted;//�����n�߂���true
	bool m_isLiftEnd;//������������true
};