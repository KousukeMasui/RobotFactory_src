#pragma once

#include"../HitInfo/HitInfo.h"

class StaticModel;
struct Line3D;
struct Sphere;
//���f���Ƃ̓����蔻����܂Ƃ߂��N���X
class ModelCollision
{
public:
	//���f���Ɛ��̓����蔻��
	static HitInfo Model_Line3D(const StaticModel& model, const MyVector3& p1, const MyVector3& p2);
	static HitInfo Model_Line3D(const StaticModel& model, const Line3D& Line3D);

	//���f���Ƌ��̓����蔻��
	static HitInfo Model_Sphere(const StaticModel& info, const Sphere& sphere);
	//���f���ƃJ�v�Z���̓����蔻��
	static HitInfo Model_Capsule(const StaticModel& info, const MyVector3& p1, const  MyVector3& p2, float radius);
};