#pragma once

#include"../../Shapes/3D/Shape3D.h"
#include"../../Shapes/Shape2D.h"

//Collideの情報を格納する構造体 現在は使わない物を除外しているので使いたいものがあったら教えて下さい。
struct HitInfo
{
	HitInfo();
	bool isHit;//当たった時true
	MyVector3 hitPosition;//当たった位置
	MyVector3 normal;

	float t;//カプセル等に場合の比率
};