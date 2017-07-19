#include "MyVector3.h"
#include<cmath>
#include<float.h>
#include"Math/MyMath.h"
MyVector3::MyVector3(float x, float y, float z) :
	x(x),
	y(y),
	z(z)
{
}

float MyVector3::Dot(const MyVector3& vec)
{
	return MyVector3::Dot(*this, vec);
}

float MyVector3::Dot(const MyVector3& v1, const MyVector3& v2)
{
	return v1.x * v2.x + v1.y * v2.y + v1.z * v2.z;
}

MyVector3 MyVector3::Cross(const MyVector3& vec)
{
	return MyVector3::Cross(*this, vec);
}

MyVector3 MyVector3::Cross(const MyVector3& v1, const MyVector3& v2)
{
	MyVector3 c = MyVector3();
	c.x = v1.y * v2.z - v1.z * v2.y;
	c.y = v1.z * v2.x - v1.x * v2.z;
	c.z = v1.x * v2.y - v1.y * v2.x;
	return c;
}

float MyVector3::Distance(const MyVector3& v1, const MyVector3& v2)
{
	MyVector3 v = v2 - v1;

	return v.Length();
}

float MyVector3::Length() const
{
	return MyVector3::Length(*this);
}

float MyVector3::Length(const MyVector3& vec)
{
	return std::sqrtf(Dot(vec, vec));
}

float MyVector3::Angle(const MyVector3& vec)
{
	return MyVector3::Angle(*this, vec);
}

float MyVector3::Angle(const MyVector3& v1, const MyVector3& v2)
{
	//ベクトルAとBの長さを計算する
	float length_A = Length(v1);
	float length_B = Length(v2);

	//内積とベクトル長さを使ってcosθを求める
	float cos_sita = MyMath::Clamp(Dot(v1, v2) / (length_A * length_B),-1.0f,1.0f);
	//cosθからθを求める
	float sita = acos(cos_sita);

	return sita;
}

MyVector3 MyVector3::Normalize()
{
	*this=MyVector3::Normalize(*this);
	return *this;
}

MyVector3 MyVector3::Normalize(const MyVector3& vec)
{
	float length = Length(vec);

	//lengthが0に限りなく近い場合
	if (length <= FLT_EPSILON)
	{
		//ゼロベクトルを返す
		return MyVector3::Zero();
	}
	float scale = 1 / length;
	return vec  * scale;
}

MyVector3 MyVector3::Zero()
{
	return MyVector3();
}

MyVector3 MyVector3::Lerp(const MyVector3& begin, const MyVector3& end, float rate)
{
	MyVector3 v = end - begin;
	return (v * rate) +begin;
}
MyVector3 operator - (const MyVector3& v)
{
	return MyVector3(-v.x, -v.y, -v.z);
}

// 代入演算子オーバーロード
MyVector3& operator +=(MyVector3& v1, const MyVector3& v2)
{
	return v1 = v1 + v2;
}

MyVector3& operator -= (MyVector3& v1, const MyVector3& v2)
{
	return v1 = v1 - v2;
}
MyVector3& operator *= (MyVector3& v, float s)
{
	return v = v * s;
}
MyVector3& operator /= (MyVector3& v, float s)
{
	return v = v / s;
}
// ２項演算子オーバーロード
MyVector3 operator + (const MyVector3& v1, const MyVector3& v2)
{
	return MyVector3(
		v1.x + v2.x,
		v1.y + v2.y,
		v1.z + v2.z);
}
MyVector3 operator - (const MyVector3& v1, const MyVector3& v2)
{
	return MyVector3(
		v1.x - v2.x,
		v1.y - v2.y,
		v1.z - v2.z);
}
MyVector3 operator * (const MyVector3& v, float s) 
{
	return MyVector3(
		v.x * s,
		v.y * s,
		v.z * s);
}
MyVector3 operator * (float s, const MyVector3& v)
{
	return v*s;
}
MyVector3 operator / (const MyVector3& v, float s)
{
	return v*(1 / s);
}
