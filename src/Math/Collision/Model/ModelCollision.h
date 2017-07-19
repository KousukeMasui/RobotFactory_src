#pragma once

#include"../HitInfo/HitInfo.h"

class StaticModel;
struct Line3D;
struct Sphere;
//モデルとの当たり判定をまとめたクラス
class ModelCollision
{
public:
	//モデルと線の当たり判定
	static HitInfo Model_Line3D(const StaticModel& model, const MyVector3& p1, const MyVector3& p2);
	static HitInfo Model_Line3D(const StaticModel& model, const Line3D& Line3D);

	//モデルと球の当たり判定
	static HitInfo Model_Sphere(const StaticModel& info, const Sphere& sphere);
	//モデルとカプセルの当たり判定
	static HitInfo Model_Capsule(const StaticModel& info, const MyVector3& p1, const  MyVector3& p2, float radius);
};