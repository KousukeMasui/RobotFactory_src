#include"MyMath.h"
#include<random>
#include"Converter.h"
float MyMath::Clamp(float num, float min, float max)//minとmaxを使っても出来るがいらないifが動く可能性があるので
{
	if (num <= min)
	{
		return min;
	}
	else if (num >= max)
	{
		return max;
	}
	return num;
}

MyVector3 MyMath::Clamp(const MyVector3 & value, const MyVector3 & min, const MyVector3 & max)
{
	return MyVector3(
		Clamp(value.x, min.x, max.x),
		Clamp(value.y, min.y, max.y),
		Clamp(value.z, min.z, max.z));
}


float MyMath::Min(float num, float min)
{
	if (num <= min)
	{
		return num;
	}
	return min;
}

float MyMath::Max(float num, float max)
{
	if (num >= max)
	{
		return num;
	}
	return max;
}

float MyMath::Distance(float n1, float n2)
{
	return std::abs(n1-n2);
}

float MyMath::Sin(float degree)
{
	return std::sinf(Converter::DegToRad(degree));
}

float MyMath::Cos(float degree)
{
	return std::cosf(Converter::DegToRad(degree));
}


float MyMath::Random(float min, float max)
{
	float result = min;

	float difference = max - min;

	float r=rand() / 32767.0f;//乱数の上限で割り、0～1にする

	return result + r*difference;
}

MyVector3 MyMath::Random(MyVector3 min, MyVector3 max)
{
	float x = Random(min.x, max.x);
	float y = Random(min.y, max.y);
	float z = Random(min.z, max.z);

	return MyVector3(x, y, z);
}

float MyMath::Lerp(float begin, float end, float rate)
{
	float value = end - begin;
	return (value * rate) + begin;
}

Color MyMath::Lerp(const Color & value1, const Color & value2, float amount)
{
	return Color(
		Lerp(value1.r, value2.r, amount),
		Lerp(value1.g, value2.g, amount),
		Lerp(value1.b, value2.b, amount),
		Lerp(value1.a, value2.a, amount));
}

float MyMath::PI = 3.14159265358979323846f;