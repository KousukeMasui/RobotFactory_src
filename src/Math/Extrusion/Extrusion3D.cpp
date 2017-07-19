#include "Extrusion3D.h"
#include<cmath>
#include"Math/Shapes/3D/BoundingBox/BoundingBox3D.h"
#include"Math/Shapes/3D/Sphere/Sphere.h"
#include"Math/Shapes/3D/Line/Line3D.h"
MyVector3 Extrusion3D::Box_ExtrusionSphere(const MyVector3& SpherePos,float radius,const MyVector3& boxPos, const MyVector3& size, const MyVector3& contactPos)
{
	//�l�p�̒��S����]���ɂ������̍��W
	MyVector3 otherPos = SpherePos - boxPos;
	MyVector3 cPos = contactPos - boxPos;

	MyVector3 toContactPos = cPos - otherPos;
	//��_�܂ł̋������قړ������ꍇ (���_���l�p�̓����̏ꍇ)
	if (toContactPos.Length() < FLT_EPSILON)
	{
		return MyVector3();
	}
	else//���_������Ă���ꍇ
	{
		return MyVector3();
	}

}

MyVector3 Extrusion3D::Box_ExtrusionSphere(const Sphere & sphere, const BoundingBox3D & box, const MyVector3 & contactPos, const MyVector3 & velocity)
{
	//1�t���[���̊Ԃ̐����쐬
	Line3D line(sphere.m_center, sphere.m_center - velocity);

	//���Ɨ����̂̌�_�����߂�
	MyVector3 cPos = box.IsCollide(line).hitPosition;
	//�ǂ̕����̖ʂɉ����o���ꂽ������
	MyVector3 normal = box.CalcNormal(cPos, line.p2);

	return sphere.m_center + (normal * sphere.m_radius);
}

MyVector3 Extrusion3D::Box_ExtrusionSphere(const MyVector3 & spherePos, float radius,
	const MyVector3 & boxPos, const MyVector3& size, const MyMatrix4 & boxRotate, const MyVector3 & contactPos)
{
	//�����̂����_�Ɉړ��������̈ʒu
	MyVector3 pos = spherePos - boxPos;
	//�����̂����_�Ɉړ�������_�̈ʒu
	MyVector3 cPos = contactPos - boxPos;
	//��]�̋t�s������߂�
	MyMatrix4 inverseRotate = MyMatrix4::InverseMatrix(boxRotate);
	//��]�Ȃ��̏ꍇ�̈ʒu�����߂�
	pos = pos * inverseRotate;
	cPos = cPos * inverseRotate;

	//��]�Ȃ��̏ꍇ�̉����o���ʒu�����߂�
	MyVector3 p = Box_ExtrusionSphere(pos, radius, MyVector3(), size, cPos);
	
	//��]������
	p = p * boxRotate;
	
	//���_���猳�̈ʒu�ɖ߂�
	p += boxPos;

	return p;
}
