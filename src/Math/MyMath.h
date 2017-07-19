#ifndef	   _MY_MATH_H_
#define	   _MY_MATH_H_

#include"Vector/MyVector3.h"
#include"Color\Color.h"
class MyMath
{
public:
	static float Clamp(float num, float min, float max);
	static MyVector3 Clamp(const MyVector3& value, const MyVector3& min, const MyVector3& max);
	static float Min(float num, float min);
	static float Max(float num, float max);
	static float Distance(float n1, float n2);
	static float Sin(float degree);
	static float Cos(float degree);
	static float Tan(float degree);
	static float ASin(float sin);
	static float ACos(float cos);
	static float ATan(float y,float x);
	static float Random(float min, float max);
	static MyVector3 Random(MyVector3 min, MyVector3 max);

	static float Lerp(float begin, float end, float rate);
	//2つのカラー間の線形補間を行います。
	static Color Lerp(const Color& value1, const Color& value2, float amount);
	static float PI;
};



#endif
