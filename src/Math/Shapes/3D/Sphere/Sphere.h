#pragma once
#include"Math/Vector/MyVector3.h"
#include"Math\Matrix\MyMatrix4.h"
#include"Math/Collision/HitInfo/HitInfo.h"
struct Line3D;
struct Capsule;
struct Sphere
{
	//�R���X�g���N�^
	Sphere(const MyVector3& center, float radius);
	//���W�����Ɋ܂܂�Ă��邩
	bool IsContains(const MyVector3& target) const;
	bool IsCollide(const Sphere& other) const;
	HitInfo IsCollide(const Line3D& line, float& t) const;
	HitInfo IsCollide(const Capsule& capsule) const;
	Sphere Transform(const MyMatrix4& pose) const;

	MyVector3 m_center;//���S���W
	float m_radius;//���a
};