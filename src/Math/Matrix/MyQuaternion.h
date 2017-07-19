#ifndef	 _MY_QUATERNION_H_
#define	 _MY_QUATERNION_H_
#include"../Vector/MyVector3.h"
#include"../Matrix/MyMatrix4.h"
//掛け算は逆順にされる
class MyQuaternion
{
public:
	// コンストラクタ
	MyQuaternion(float x = 0.0f, float y = 0.0f, float z = 0.0f, float w = 1.0f);
	// コンストラクタ
	MyQuaternion(const MyVector3& axis, float degree);
	static MyQuaternion CreateQuaternion(const MyMatrix4& m);
	// 正規化する
	static MyQuaternion Normalize(const MyQuaternion& q);
	// 正規化する
	MyQuaternion Normalize();

	// 内積を求める
	static float Dot(const MyQuaternion& q1, const MyQuaternion& q2);

	float Dot(const MyQuaternion & q) const;
	// ノルムを求める
	float Length() const;

	// 球面線形補間
	static MyQuaternion Slerp(const MyQuaternion& value1, const MyQuaternion& value2, float amount);
	
public:
	float x;
	float y;
	float z;
	float w;
};

// 単項演算子オーバーロード
MyQuaternion operator - (const MyQuaternion& q);

// 代入演算子オーバーロード
MyQuaternion& operator += (MyQuaternion& q1, const MyQuaternion& q2);
MyQuaternion& operator -= (MyQuaternion& q1, const MyQuaternion& q2);
MyQuaternion& operator *= (MyQuaternion& q, float s);
MyQuaternion& operator /= (MyQuaternion& q, float s);
MyQuaternion& operator *= (MyQuaternion& q1, const MyQuaternion& q2);

// ２項演算子オーバーロード
MyQuaternion operator + (const MyQuaternion& q1, const MyQuaternion& q2);
MyQuaternion operator - (const MyQuaternion& q1, const MyQuaternion& q2);
MyQuaternion operator * (const MyQuaternion& q1, const MyQuaternion& q2);
MyQuaternion operator * (const MyQuaternion& q, float s);
MyQuaternion operator * (float s, const MyQuaternion& q);
MyQuaternion operator / (const MyQuaternion& q, float s);

#endif