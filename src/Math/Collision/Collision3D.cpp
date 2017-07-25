#include "Collision3D.h"
#include "../Shapes/3D/BoundingBox/BoundingBox3D.h"
#include"../MyMath.h"

#include"../Shapes/3D/Sphere/Sphere.h"
#include"../Shapes/3D/Capsule/Capsule.h"

bool Collision3D::Line_Sphere(const MyVector3 & p1, const MyVector3 & p2, float radius, const MyVector3 & circlePos, MyVector3 & contactPoint)
{
	MyVector3 v = p2 - p1;//���̕����x�N�g��
	MyVector3 v1 = circlePos - p1;//�n�_���狅�̂ւ̕����x�N�g��

	float t = MyVector3::Dot(v, v1) / MyVector3::Dot(v, v);

	MyVector3 vt = t * v;
	MyVector3 vn = v1 - vt;

	//p1�̊O����
	if (0 < t && v1.Length() < radius)
	{
		contactPoint = p1;
		return true;
	}
	MyVector3 v2 = circlePos - p2;
	if (t > 1 && v2.Length() < radius)//v2���O��
	{
		contactPoint = p2;
		return true;
	}
	if ((0 < t && t < 1) && vn.Length() < radius)
	{
		MyVector3 vr = MyVector3::Normalize(vn) * radius;
		contactPoint = p1 + vt;
		return true;
	}
	return false;
}

bool Collision3D::Ray_Sphere(const MyVector3 & rayPos, const MyVector3 & direction, const MyVector3 & spherePos, float radius, float & t, MyVector3 & q)
{
	MyVector3 m = rayPos - spherePos;
	float b = MyVector3::Dot(m, direction);
	float c = MyVector3::Dot(m, m) - radius * radius;
	// r�̌��_��s�̊O���ɂ���(c > 0)�Ar��s���痣��Ă����������w���Ă���ꍇ(b > 0)�ɏI��
	if (c > 0.0f && b > 0.0f) return false;
	float discr = b*b - c;
	// ���̔��ʎ��͌����������O��Ă��邱�ƂɈ�v
	if (discr < 0.0f) return false;
	// ����Ō����͋��ƌ������Ă��邱�Ƃ�������A��������ŏ��̒lt���v�Z
	t = -b - std::sqrt(discr);
	// t�����ł���ꍇ�A�����͋��̓�������J�n���Ă���̂�t���[���ɃN�����v
	if (t < 0.0f) t = 0.0f;
	q = rayPos + t * direction;
	return true;
}

/// <summary>
/// ���̂ƃJ�v�Z���^�̓����蔻��
/// </summary>
/// <param name="p1">�J�v�Z���̎n�_</param>
/// <param name="p2">�J�v�Z���̏I�_</param>
/// <param name="circlePos">���̂̈ʒu</param>
/// <param name="r1">�J�v�Z���̔��a</param>
/// <param name="r2">���̂̔��a</param>
/// <returns></returns>

bool Collision3D::Capsule_BoundarySphere(MyVector3 p1, MyVector3 p2, MyVector3 & circlePos, float r1, float r2, MyVector3 & contactPoint)
{
	return Line_Sphere(p1, p2, r1 + r2, circlePos, contactPoint);
}
/// <summary>
/// �ǂƓ��̂̔��ˏ���
/// </summary>
/// <param name="velocity">���̂̈ړ���</param>
/// <param name="normal">�ǂ̖@���x�N�g��</param>
/// <param name="e">�����W��</param>

void Collision3D::Reflection(MyVector3 & velocity, MyVector3 normal, float e)
{
	MyVector3 vn = -MyVector3::Dot(velocity, normal) * normal;
	MyVector3 vt = velocity + vn;
	velocity = vn * e + vt;
}

/// <summary>
/// ���̓��m�̔��ˏ���
/// </summary>
/// <param name="velocity1">����1�̕����x�N�g��</param>
/// <param name="position1">����1�̈ʒu</param>
/// <param name="radius1">����1�̔��a</param>
/// <param name="velocity2">����2�̕����x�N�g��</param>
/// <param name="position2">����2�̈ʒu</param>
/// <param name="radius2">����2�̔��a</param>
/// <param name="e">�����W��</param>
/// <param name="massRaito">���ʔ�</param>

void Collision3D::Reflection(MyVector3 & velocity1, MyVector3 & position1, float radius1, MyVector3 & velocity2, MyVector3 & position2, float radius2, float e, float massRaito)
{
	//���̂̒��S�����񂾕����x�N�g��
	MyVector3 n = MyVector3::Normalize(position2 - position1);

	//����1�̐i�ޕ����@���S����n�@�ڐ�����t
	MyVector3 v1n = MyVector3::Dot(velocity1, n) * n;
	MyVector3 v1t = velocity1 - v1n;

	//����2�̐i�ޕ����@���S����n�@�ڐ�����t
	MyVector3 v2n = MyVector3::Dot(velocity2, n) * n;
	MyVector3 v2t = velocity2 - v1n;

	//���ʔ�Ɣ������l��������
	velocity1 = (v2n - v1n) * (1 + e) / (massRaito + 1) + velocity1;
	velocity2 = (v1n - v2n) * (1 + e) / (1 / massRaito + 1) + velocity2;
}

bool Collision3D::Capsule_Capsule(MyVector3 p1, MyVector3 p2, float r1, MyVector3 p3, MyVector3 p4, float r2)
{
	MyVector3 a = p2 - p1;//����1�̕����x�N�g��
	MyVector3 b = p4 - p3;//����2�̕����x�N�g��
	MyVector3 c = p3 - p1;

	MyVector3 n = MyVector3::Cross(a, b);

	MyVector3 N = MyVector3::Normalize(n);
	float L = MyVector3::Dot(c, N);

	MyVector3 n1 = MyVector3::Cross(a, N);
	MyVector3 n2 = MyVector3::Cross(b, N);

	MyVector3 P3 = p3 - N * L;
	MyVector3 P4 = p4 - N * L;

	MyVector3 v1 = p1 - P3;
	MyVector3 v2 = p2 - P3;
	MyVector3 v3 = P3 - p1;
	MyVector3 v4 = P4 - p1;

	float L1 = MyVector3::Dot(v1, n2);
	float L2 = MyVector3::Dot(v2, n2);
	float L3 = MyVector3::Dot(v3, n1);
	float L4 = MyVector3::Dot(v4, n1);

	float t1 = L3 / (L3 - L4);
	float t2 = L1 / (L1 - L2);

	//p1��p2�̓����̏ꍇ
	if ((t1 > 0 && t1 < 1) && (t2 > 0 && t2 < 1) && (std::abs(L) < r1 + r2))
	{
		MyVector3 vd = (N * (r1 + r2)*std::signbit(L));//�����o����

		p3 = P3 + vd;
		p4 = P4 + vd;

		return true;
	}

	//p�@�����̂���Ȃ������̕ϐ�     pp �����蔻��̉����o���O�̈ʒu
	MyVector3 p, pp;
	p = MyVector3::Zero();
	pp = p1;//�ړ��O��p1��ۑ�
			//p1���O���̏ꍇ
	if (t1 < 0 && Capsule_BoundarySphere(p3, p4, p1, r1, r2, p))
	{
		return true;
	}
	//p2���O���̏ꍇ
	else if (t1> 0 && Capsule_BoundarySphere(p3, p4, p2, r1, r2, p))
	{
		return true;
	}
	return false;
}


void Collision3D::ClosestPtPointOBB(const MyVector3 & p, const MyVector3 & boxPos, const MyMatrix4 & boxRotate, const MyVector3 & boxSize, MyVector3 & q)
{
	MyVector3 d = p - boxPos;
	// ���̒��S�ɂ����錋�ʂ���J�n�A��������i�K�I�ɐi�߂�
	q = boxPos;

	MyVector3 u[3];
	u[0] = boxRotate.GetLeft();
	u[1] = boxRotate.GetTop();
	u[2] = boxRotate.GetForward();

	float size[3];
	size[0] = boxSize.x;
	size[1] = boxSize.y;
	size[2] = boxSize.z;

	// �eOBB�̎��ɑ΂���...
	for (int i = 0; i < 3; i++) {
		// d�����̎��Ɏˉe����
		// ���̒��S����d�̎��ɉ����������𓾂�
		float dist = MyVector3::Dot(d, u[i]);
		// ���͈̔͂����������傫���ꍇ�A���܂ŃN�����v
		if (dist > size[i]) dist = size[i];
		if (dist < -size[i]) dist = -size[i];
		// ���[���h���W�𓾂邽�߂ɂ��̋����������ɉ����Đi�߂�
		q += dist * u[i];
	}
}

bool Collision3D::TestSphereOBB(const MyVector3 & spherePos, float sphereRadius, const MyVector3 & boxPos, const MyMatrix4 & boxRotate, const MyVector3 & boxSize, MyVector3 & p)
{
	// ���̒��S�ɑ΂���ŋߐړ_�ł���OBB��ɂ���_p��������
	ClosestPtPointOBB(spherePos, boxPos, boxRotate, boxSize, p);

	// ����OBB����������̂́A���̒��S����_p�܂ł�(��������)������
	// (��������)���̔��a�����������ꍇ
	MyVector3 v = p - spherePos;
	return v.Length() <= sphereRadius;
}