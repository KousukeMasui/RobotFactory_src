#include"MyQuaternion.h"
#include"../Converter.h"
#include<cmath>
#include"Math/MyMath.h"
// コンストラクタ
MyQuaternion::MyQuaternion(float x, float y, float z, float w):
x(x),
y(y),
z(z),
w(w)
{

}
// コンストラクタ
MyQuaternion::MyQuaternion(const MyVector3& axis, float degree)
{
	float sin = MyMath::Sin(degree / 2.0f);
	x = sin * axis.x;
	y = sin * axis.y;
	z = sin * axis.z;
	w = MyMath::Cos(degree / 2.0f);
}

MyQuaternion MyQuaternion::CreateQuaternion(const MyMatrix4 & m)
{
	MyQuaternion result;
	float tr = m.m[0][0] + m.m[1][1] + m.m[2][2] + m.m[3][3];
	if (tr >= 1.0f) {
		float fourD = 2.0f * std::sqrt(tr);
		result.x = (m.m[1][2] - m.m[2][1]) / fourD;
		result.y = (m.m[2][0] - m.m[0][2]) / fourD;
		result.z = (m.m[0][1] - m.m[1][0]) / fourD;
		result.w = fourD / 4.0f;
		return result;
	}
	int i = 0;
	if (m.m[0][0] <= m.m[1][1]) {
		i = 1;
	}
	if (m.m[2][2] > m.m[i][i]) {
		i = 2;
	}
	int j = (i + 1) % 3;
	int k = (j + 1) % 3;
	tr = m.m[i][i] - m.m[j][j] - m.m[k][k] + 1.0f;
	float fourD = 2.0f * std::sqrt(tr);
	float qa[4];
	qa[i] = fourD / 4.0f;
	qa[j] = (m.m[j][i] + m.m[i][j]) / fourD;
	qa[k] = (m.m[k][i] + m.m[i][k]) / fourD;
	qa[3] = (m.m[j][k] - m.m[k][j]) / fourD;
	result.x = qa[0];
	result.y = qa[1];
	result.z = qa[2];
	result.w = qa[3];
	return result;
}

MyQuaternion MyQuaternion::Normalize(const MyQuaternion & q)
{
	return q / q.Length();
}

MyQuaternion MyQuaternion::Normalize()
{
	return *this = Normalize(*this);
}

float MyQuaternion::Dot(const MyQuaternion & q1, const MyQuaternion & q2)
{
	return q1.x*q2.x + q1.y*q2.y + q1.z*q2.z + q1.w * q2.w;
}

float MyQuaternion::Dot(const MyQuaternion & q) const
{
	return x * q.x + y * q.y + z * q.z + w * q.w;
}

float MyQuaternion::Length() const
{
	return std::sqrtf(Dot(*this,*this));
}


MyQuaternion MyQuaternion::Slerp(const MyQuaternion & value1, const MyQuaternion & value2, float amount)
{
	float cos = Dot(value1, value2);
	MyQuaternion t2 = value2;
	if (cos < 0.0f)
	{
		cos = -cos;
		t2 = -value2;
	}
	float k0 = 1.0f - amount;
	float k1 = amount;
	if ((1.0f - cos)>0.001f)
	{
		float theta = std::acos(cos);
		k0 = std::sin(theta * k0) / std::sin(theta);
		k1 = std::sin(theta * k1) / std::sin(theta);
	}
	return (value1 * k0) + (value2 * k1);
}

MyQuaternion operator-(const MyQuaternion & q)
{
	return MyQuaternion(-q.x,-q.y,-q.z,-q.w);
}

MyQuaternion & operator+=(MyQuaternion & q1, const MyQuaternion & q2)
{
	q1.x += q2.x;
	q1.y += q2.y;
	q1.z += q2.z;
	q1.w += q2.w;

	return q1;
}

MyQuaternion & operator-=(MyQuaternion & q1, const MyQuaternion & q2)
{
	q1.x -= q2.x;
	q1.y -= q2.y;
	q1.z -= q2.z;
	q1.w -= q2.w;

	return q1;
}

MyQuaternion & operator*=(MyQuaternion & q, float s)
{
	q.x *= s;
	q.y *= s;
	q.z *= s;
	q.w *= s;

	return q;
}

MyQuaternion & operator/=(MyQuaternion & q, float s)
{
	return q *= (1.0f / s);
}

MyQuaternion & operator*=(MyQuaternion & q1, const MyQuaternion & q2)
{
	q1 = MyQuaternion(
		q1.x * q2.w + q1.y * q2.z - q1.z * q2.y + q1.w * q2.x,
	   -q1.x * q2.z + q1.y * q2.w + q1.z * q2.x + q1.w * q2.y,
		q1.x * q2.y - q1.y * q2.x + q1.z * q2.w + q1.w * q2.z,
	   -q1.x * q2.x - q1.y * q2.y - q1.z * q2.z + q1.w * q2.w
		);

	return q1;
}

MyQuaternion operator+(const MyQuaternion& q1, const MyQuaternion & q2)
{
	return MyQuaternion(q1) += q2;
}

MyQuaternion operator-(const MyQuaternion& q1, const MyQuaternion & q2)
{
	return MyQuaternion(q1) -= q2;
}

MyQuaternion operator*(const MyQuaternion& q1, const MyQuaternion & q2)
{
	return MyQuaternion(q1) *= q2;
}

MyQuaternion operator*(const MyQuaternion& q, float s)
{
	return MyQuaternion(q) *=s;
}

MyQuaternion operator*(float s, const MyQuaternion& q)
{
	return MyQuaternion(q) *= s;
}

MyQuaternion operator/(const MyQuaternion& q, float s)
{
	return MyQuaternion(q) /=s;
}
