#ifndef	 _MY_QUATERNION_H_
#define	 _MY_QUATERNION_H_
#include"../Vector/MyVector3.h"
#include"../Matrix/MyMatrix4.h"
//�|���Z�͋t���ɂ����
class MyQuaternion
{
public:
	// �R���X�g���N�^
	MyQuaternion(float x = 0.0f, float y = 0.0f, float z = 0.0f, float w = 1.0f);
	// �R���X�g���N�^
	MyQuaternion(const MyVector3& axis, float degree);
	static MyQuaternion CreateQuaternion(const MyMatrix4& m);
	// ���K������
	static MyQuaternion Normalize(const MyQuaternion& q);
	// ���K������
	MyQuaternion Normalize();

	// ���ς����߂�
	static float Dot(const MyQuaternion& q1, const MyQuaternion& q2);

	float Dot(const MyQuaternion & q) const;
	// �m���������߂�
	float Length() const;

	// ���ʐ��`���
	static MyQuaternion Slerp(const MyQuaternion& value1, const MyQuaternion& value2, float amount);
	
public:
	float x;
	float y;
	float z;
	float w;
};

// �P�����Z�q�I�[�o�[���[�h
MyQuaternion operator - (const MyQuaternion& q);

// ������Z�q�I�[�o�[���[�h
MyQuaternion& operator += (MyQuaternion& q1, const MyQuaternion& q2);
MyQuaternion& operator -= (MyQuaternion& q1, const MyQuaternion& q2);
MyQuaternion& operator *= (MyQuaternion& q, float s);
MyQuaternion& operator /= (MyQuaternion& q, float s);
MyQuaternion& operator *= (MyQuaternion& q1, const MyQuaternion& q2);

// �Q�����Z�q�I�[�o�[���[�h
MyQuaternion operator + (const MyQuaternion& q1, const MyQuaternion& q2);
MyQuaternion operator - (const MyQuaternion& q1, const MyQuaternion& q2);
MyQuaternion operator * (const MyQuaternion& q1, const MyQuaternion& q2);
MyQuaternion operator * (const MyQuaternion& q, float s);
MyQuaternion operator * (float s, const MyQuaternion& q);
MyQuaternion operator / (const MyQuaternion& q, float s);

#endif