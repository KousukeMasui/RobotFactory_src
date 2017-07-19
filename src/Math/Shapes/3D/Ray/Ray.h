#ifndef	_RAY_H_
#define	_RAY_H_

#include"Math/Vector/MyVector3.h"
#include"Math/Vector/MyVector2.h"
#include"Math/Matrix/MyMatrix4.h"

struct Ray
{
	Ray(const MyVector3& position, const MyVector3& direction);


	// 2D座標からレイを計算する
	static Ray CalculateRay(
		const MyVector2& position,	// スクリーン座標
		const MyMatrix4& screen,		// スクリーン変換行列
		const MyMatrix4& projection,	// 透視変換行列
		const MyMatrix4& view			// 視野変換行列
		);
	~Ray();

	Ray Transform(const MyMatrix4& matrix);

	MyVector3 m_position;
	//向き
	MyVector3 m_direction;
};

#endif