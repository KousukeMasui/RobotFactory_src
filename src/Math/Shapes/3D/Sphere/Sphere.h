#pragma once
#include"Math/Vector/MyVector3.h"
#include"Math\Matrix\MyMatrix4.h"
#include"Math/Collision/HitInfo/HitInfo.h"
struct Line3D;
struct Capsule;
struct Sphere
{
	//コンストラクタ
	Sphere(const MyVector3& center, float radius);
	//座標が球に含まれているか
	bool IsContains(const MyVector3& target) const;
	bool IsCollide(const Sphere& other) const;
	HitInfo IsCollide(const Line3D& line, float& t) const;
	HitInfo IsCollide(const Capsule& capsule) const;
	Sphere Transform(const MyMatrix4& pose) const;

	MyVector3 m_center;//中心座標
	float m_radius;//半径
};