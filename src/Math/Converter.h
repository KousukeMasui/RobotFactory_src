#ifndef		 _CONVERTER_H_
#define		 _CONVERTER_H_
#include<DxLib.h>
#include"Vector/MyVector3.h"
class MyMatrix4;
class Converter
{
public:
	static VECTOR MyVector3ToVECTOR(const MyVector3& vec);
	static MyVector3 VECTORToMyVector3(const VECTOR& vec);
	static MATRIX MyMatirx4ToMATRIX(const MyMatrix4& mat);
	static MyMatrix4 MATRIXToMyMatrix4(const MATRIX& mat);
	static float DegToRad(float degree);
	static float RadToDeg(float radian);
};

#endif