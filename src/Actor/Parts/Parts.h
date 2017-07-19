#pragma once
class IWorld;

#include"Model/Model/Model.h"
#include"Actor/LiftObject/LiftObject.h"
class Parts : public LiftObject
{
public:
	Parts(IWorld& world,const MyVector3& position);
	~Parts();

	void Draw()const;

	bool IsDelete() const override;

	void LiftDown(FactoryPtr factory) override;

	Sphere GetSphere() const override;
private:
	IWorld& m_world;
	Model m_model;
	Sphere m_sphere;
	bool m_isDelete;//Ú’n‚µ‚Ä‚¢‚étrue
	
};