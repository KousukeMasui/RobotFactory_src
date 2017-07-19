#ifndef	  _COLLISION_3D_H_
#define	  _COLLISION_3D_H_

#include"../Vector/MyVector3.h"
#include"../Vector/MyVector2.h"
#include"../Matrix/MyMatrix4.h"
#include<vector>
#include"../Shapes/3D/Shape3D.h"
#include"../Shapes\Shapes.h"
#include"Math/Converter.h"
#include"Model/StaticModel/StaticModel.h"


struct Sphere;
struct BoundingBox3D;
struct Line3D;
struct Capsule;
#include"HitInfo/HitInfo.h"

class Collision3D
{
public:

	/// <summary>
	/// ���Ƌ��̓����蔻�� �����o������
	/// </summary>
	/// <param name="p1">���̎n�_</param>
	/// <param name="p2">���̏I�_</param>
	/// <param name="radius">���a</param>
	/// <param name="circlePos">���̈ʒu</param>
	/// <param name="contactMyVector3">�ړ_</param>
	/// <returns></returns>
	static bool Line_Sphere_Extrusion(const MyVector3& p1,const MyVector3& p2, float radius, MyVector3& circlePos, MyVector3& contactPoint);
	//�����o���Ȃ�
	static bool Line_Sphere(const MyVector3& p1, const MyVector3& p2, float radius,const MyVector3& circlePos,MyVector3& contactPoint);

	
	//ray�Ƌ��̓����蔻��
	static bool Ray_Sphere(const MyVector3& rayPos, const MyVector3& direction, const MyVector3& spherePos, float radius, float &t, MyVector3 &q);
	
	/// <summary>
	/// ���̂ƃJ�v�Z���^�̓����蔻��
	/// </summary>
	/// <param name="p1">�J�v�Z���̎n�_</param>
	/// <param name="p2">�J�v�Z���̏I�_</param>
	/// <param name="circlePos">���̂̈ʒu</param>
	/// <param name="r1">�J�v�Z���̔��a</param>
	/// <param name="r2">���̂̔��a</param>
	/// <returns></returns>
	static bool Capsule_BoundarySphere(MyVector3 p1, MyVector3 p2, MyVector3& circlePos, float r1, float r2, MyVector3& contactMyVector3);

	/// <summary>
	/// �ǂƓ��̂̔��ˏ���
	/// </summary>
	/// <param name="velocity">���̂̈ړ���</param>
	/// <param name="normal">�ǂ̖@���x�N�g��</param>
	/// <param name="e">�����W��</param>
	static void Reflection(MyVector3& velocity, MyVector3 normal, float e);

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
	static void Reflection(
		MyVector3& velocity1,MyVector3& position1, float radius1,
		MyVector3& velocity2,MyVector3& position2, float radius2,
		float e,
		float massRaito);

	static bool Capsule_Capsule(MyVector3 p1, MyVector3 p2, float r1, MyVector3 p3, MyVector3 p4, float r2);

	// �^����ꂽ�_p�ɑ΂��āAAABB b�̏�������͒��ɂ���p�̍ŋߐړ_q��Ԃ�
	static void ClosestPtPointAABB(MyVector3 position, MyVector3 boxPos,MyVector3 boxSize, MyVector3 &qPos)
	{
		float p[3];
		p[0] = position.x;
		p[1] = position.y;
		p[2] = position.z;
		float q[3];

		float min[3];
		min[0] = boxPos.x - boxSize.x;
		min[1] = boxPos.y - boxSize.y;
		min[2] = boxPos.z - boxSize.z;
		float max[3];
		max[0] = boxPos.x + boxSize.x;
		max[1] = boxPos.y + boxSize.y;
		max[2] = boxPos.z + boxSize.z;

		// �e���W���ɑ΂��āA�_�̍��W�l�����̊O���ɂ���ꍇ��
		// ���܂œ_���N�����v�A�����łȂ���΂��̂܂�
		for (int i = 0; i < 3; i++) {
			float v = p[i];
			if (v < min[i]) v = min[i]; // v = max(v, b.min[i])
			if (v > max[i]) v = max[i]; // v = min(v, b.max[i])
			q[i] = v;
		}

		qPos = MyVector3(q[0], q[1], q[2]);
	}

	// �^����ꂽ�_p�ɑ΂��āAOBB b�̏�(�������͒�)�ɂ���p�̍ŋߐړ_q��Ԃ�
	static void ClosestPtPointOBB(const MyVector3& p, const MyVector3& boxPos, const MyMatrix4& boxRotate, const MyVector3& boxSize, MyVector3 &q);

	// ��s��OBB b�Ɍ������Ă���ꍇ�͐^��Ԃ��A�����łȂ���΋U��Ԃ�
	// ���̒��S�ɑ΂���OBB��̍ŋߐړ_�ł���_p���Ԃ�
	static bool TestSphereOBB(const MyVector3& spherePos, float sphereRadius, const MyVector3& boxPos, const MyMatrix4& boxRotate, const MyVector3& boxSize, MyVector3 &p);


};

#endif