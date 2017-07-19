#pragma once
#include"Object/Object.h"
#include"Math/Shapes/3D/Sphere/Sphere.h"
#include"Model/Model/Model.h"
#include"Base/GameUsing.h"
#include<forward_list>
class IWorld;
//�V�����J�[�\���N���X�@����Ɠ������Ă���L�����A�H���I���ł���悤�ɂ���
class SelectCursor : public Object
{
public:
	explicit SelectCursor(const MyVector3& position);
	~SelectCursor();

	//�X�V �w�肳�ꂽ�ʒu�܂ł��ړ�����
	virtual void Update(const MyVector3& targetPosition,float deltaTime);
	//�`��
	void Draw(const Color& color) const;
	//�����蔻��
	UnitPtr IsCollide(IWorld& world,InfluenceID id) const;
	UnitPtr IsCollide(const UnitPtrs& units) const;
	FactoryPtr IsCollide(const FactoryPtrs& factorys) const;
	bool IsCollide(const UnitFactory* unit) const;
	Sphere GetSphere() const;
	bool IsCollide(const Sphere& sphere) const;

	//�T�C�Y�ύX
	void Scale(const MyVector3& scale);
private:
	Model m_model;
	//�T�C�Y
	MyVector3 m_scale;
protected:
	//�����蔻��p��
	Sphere m_sphere;
};