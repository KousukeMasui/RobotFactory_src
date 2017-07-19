#ifndef		_MY_VECTOR_2_H_
#define		_MY_VECTOR_2_H_

class MyVector2
{
public:
	MyVector2(float x=0.0f, float y=0.0f);

	float Length();
	static float Length(MyVector2 v);

	float Distance(MyVector2 v);
	static float Distance(MyVector2 v1, MyVector2 v2);

	float Dot(MyVector2 v);
	static float Dot(MyVector2 v1, MyVector2 v2);

	float Cross(MyVector2 v);
	static float Cross(MyVector2 v1, MyVector2 v2);

	MyVector2 Normalize();
	static MyVector2 Normalize(MyVector2 v);

	float Angle(MyVector2 v);
	static float Angle(MyVector2 v1, MyVector2 v2);
	//minからmaxの範囲にいたらtrue
	bool Inside(MyVector2 min, MyVector2 max);
	static bool Inside(MyVector2 p, MyVector2 min, MyVector2 max);


	///<summary>ベクトルの線間補正</summary>
	///<param name='begin'>スタート位置</param>
	///<param name='end'>終了位置</param>
	///<param name='rate'>割合(0.0～1.0)</param>
	static MyVector2 Lerp(MyVector2 begin, MyVector2 end, float rate);
public:
	float x;
	float y;
};

MyVector2 operator -(const MyVector2& v);

MyVector2& operator +=(MyVector2& v1, const MyVector2 v2);
MyVector2& operator -=(MyVector2& v1, const MyVector2 v2);
MyVector2& operator *=(MyVector2& v1, const float s);
MyVector2& operator /=(MyVector2& v1, const float s);

MyVector2 operator +(MyVector2 v1, MyVector2 v2);
MyVector2 operator -(MyVector2 v1, MyVector2 v2);
MyVector2 operator *(MyVector2 v, float s);
MyVector2 operator *(float s, MyVector2 v);
MyVector2 operator /(MyVector2 v, float s);

#endif