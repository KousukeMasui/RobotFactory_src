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
//持ち上げられるオブジェクトの親クラス
class LiftObject : public Object
{
public:
	LiftObject(LIFT_ID id,const MyVector3& position);
	~LiftObject();

	void LiftStart();
	void LiftEnd();
	//持ち上げられる関数
	void LiftUp(Unit& unit);
	//下ろした際の処理
	virtual void LiftDown(FactoryPtr factory) = 0;
	void LiftUpEnd();
	bool IsLiftStart() const;//持ち始められたらtrue
	bool IsLiftEnd() const;//持ち終わったか

	LIFT_ID GetID() const;

	virtual bool IsDelete() const = 0;

	virtual Sphere GetSphere() const = 0;
private:
	LIFT_ID m_id;
protected:
	bool m_isLifted;//持ち始めたらtrue
	bool m_isLiftEnd;//持ちきったらtrue
};