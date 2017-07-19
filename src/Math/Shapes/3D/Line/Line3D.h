#ifndef	_LINE_3D_H_
#define	_LINE_3D_H_

#include"Math/Vector/MyVector3.h"
#include"Math/Matrix/MyMatrix4.h"
#include"../Shape3D.h"
struct Line3D : public Shape3D
{
	Line3D(const MyVector3& start, const MyVector3& end);
	//長さを返す
	float Length() const;
	//始点から終点への方向を返す
	MyVector3 Direction() const;
	//点までの最短距離を求める
	float PointLength(const MyVector3& point) const;

	//座標変換
	Line3D Transform(const MyMatrix4& matrix);

	void Translate(const MyVector3& position) override;

	MyVector3 m_start;
	MyVector3 m_end;
};

#endif