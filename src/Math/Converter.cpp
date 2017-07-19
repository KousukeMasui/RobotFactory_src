#include "Converter.h"
//âΩåÃÇ©math.hÇ©ÇÁéùÇ¡ÇƒÇ±ÇÍÇ»Ç¢ÇÃÇ≈ÉRÉsÉy
#define M_PI       3.14159265358979323846   // pi
#include"Matrix/MyMatrix4.h"
VECTOR Converter::MyVector3ToVECTOR(const MyVector3& vec)
{
	VECTOR v;
	v.x = vec.x;
	v.y = vec.y;
	v.z = vec.z;

	return v;
}

MyVector3 Converter::VECTORToMyVector3(const VECTOR& vec)
{
	MyVector3 v;

	v.x = vec.x;
	v.y = vec.y;
	v.z = vec.z;

	return v;
}

MATRIX Converter::MyMatirx4ToMATRIX(const MyMatrix4& mat)
{
	MATRIX m;
	for (int i = 0; i < 4; i++)
	{
		for (int j = 0; j < 4; j++)
		{
			m.m[i][j] = mat.m[i][j];
		}
	}

	return m;
}

MyMatrix4 Converter::MATRIXToMyMatrix4(const MATRIX& mat)
{
	MyMatrix4 m;
	for (int i = 0; i < 4; i++)
	{
		for (int j = 0; j < 4; j++)
		{
			m.m[i][j] = mat.m[i][j];
		}
	}

	return m;
}

float Converter::DegToRad(float degree) 
{
	return degree*(float)M_PI / 180.0f;
}
float Converter::RadToDeg(float radian)
{
	return radian* 180.0f / (float)M_PI;
}
