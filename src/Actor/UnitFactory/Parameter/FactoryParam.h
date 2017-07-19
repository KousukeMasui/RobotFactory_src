#pragma once

#include"Actor\Influence\InfluenceID.h"
#include"Object/Object.h"
#include"Math/Shapes/3D/BoundingBox/BoundingBox3D.h"
//managerクラスで使うパラメータ
struct FactoryParam : public Object
{
	FactoryParam(const MyVector3& position, InfluenceID influence) :
		Object(position, MyMatrix4::Identity()),
		influence(influence),
		m_box(MyVector3(-1516.249f,-1285.357f,-3948.094f) * 0.025f,MyVector3(2490.878f, 1285.357f, 3948.094f) * 0.025f,position)
	{
	}
	InfluenceID influence;
	BoundingBox3D m_box;
};