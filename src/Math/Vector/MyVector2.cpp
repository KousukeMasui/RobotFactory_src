#include "MyVector2.h"
#include<cmath>

MyVector2::MyVector2(float x, float y):
	x(x),
	y(y)
{
}

float MyVector2::Length()
{
	return Length(*this);
}

float MyVector2::Length(MyVector2 v)
{
	return std::sqrtf(v.x*v.x + v.y*v.y);
}

float MyVector2::Distance(MyVector2 v)
{
	return Distance(*this,v);
}

float MyVector2::Distance(MyVector2 v1, MyVector2 v2)
{
	MyVector2 v = v2 - v1;

	return v.Length();
}

float MyVector2::Dot(MyVector2 v)
{
	return Dot(*this,v);
}

float MyVector2::Dot(MyVector2 v1, MyVector2 v2)
{
	return v1.x * v2.x + v1.y * v2.y;
}

float MyVector2::Cross(MyVector2 v)
{
	return Cross(*this,v);
}

float MyVector2::Cross(MyVector2 v1, MyVector2 v2)
{
	return v1.x*v2.y - v1.y*v2.x;
}

MyVector2 MyVector2::Normalize()
{
	float value = 1.0f / Length();

	*this *= value;

	return *this;

}

MyVector2 MyVector2::Normalize(MyVector2 v)
{
	return v.Normalize();
}

float MyVector2::Angle(MyVector2 v)
{
	return Angle(*this, v);
}

float MyVector2::Angle(MyVector2 v1, MyVector2 v2)
{	//ベクトルAとBの長さを計算する
	float length_A = Length(v1);
	float length_B = Length(v2);

	//内積とベクトル長さを使ってcosθを求める
	float cos_sita = Dot(v1, v2) / (length_A * length_B);
	//cosθからθを求める
	float sita = acos(cos_sita);

	return sita;
}

bool MyVector2::Inside(MyVector2 min, MyVector2 max)
{
	if (min.x > x || max.x < x) return false;
	if (min.y > y || max.y < y) return false;
	return true;
}

bool MyVector2::Inside(MyVector2 p, MyVector2 min, MyVector2 max)
{
	return p.Inside(min, max);
}

MyVector2 MyVector2::Lerp(MyVector2 begin, MyVector2 end, float rate)
{
	MyVector2 v = end - begin;
	return (v * rate) + begin;
}

MyVector2 operator-(const MyVector2 & v)
{
	MyVector2 result;
	result.x = -v.x;
	result.y = -v.y;

	return result;
}

MyVector2& operator+=(MyVector2& v1, const MyVector2 v2)
{
	v1.x += v2.x;
	v1.y += v2.y;

	return v1;
}

MyVector2& operator-=(MyVector2 & v1, const MyVector2 v2)
{
	v1.x -= v2.x;
	v1.y -= v2.y;

	return v1;
}

MyVector2& operator*=(MyVector2 & v1, const float s)
{
	v1.x *= s;
	v1.y *= s;

	return v1;
}

MyVector2& operator/=(MyVector2 & v1, const float s)
{
	v1.x /= s;
	v1.y /= s;

	return v1;
}

MyVector2 operator+(MyVector2 v1, MyVector2 v2)
{
	return v1 += v2;
}

MyVector2 operator-(MyVector2 v1, MyVector2 v2)
{
	return v1 -= v2;
}

MyVector2 operator*(MyVector2 v, float s)
{
	return v *= s;
}

MyVector2 operator*(float s, MyVector2 v)
{
	return v*s;
}

MyVector2 operator/(MyVector2 v, float s)
{
	return v /=s;
}
