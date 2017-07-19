#ifndef		   _ShapeS_H_
#define		   _ShapeS_H_

#include"../Vector/MyVector3.h"
#include"../Vector/MyVector2.h"
#include<vector>
#include"3D/Shape3D.h"
#include"Shape2D.h"
#include"3D/Line/Line3D.h"
#include<DxLib.h>
#include"Math/Converter.h"
enum Shape3DEnum
{
	SPHERE_3D,
	LINE_3D,
	CAPSULE_3D,
	POLIGON_3D,
	BOX_3D
};

enum Shape2DEnum
{
	SPHERE_2D,
	LINE_2D
};

/*時間がないのと、行数が少ないのでまとめて置く。
　時間があったら分解*/


/*2D用、一つの軸をムシした当たり判定の場合は積極的にこちらとCollision2Dを使ってください*/
struct Line2D :public Shape2D
{
public:
	MyVector2 vec() { return p2 - p1; }
	Line2D() :
		Shape2D()
	{
	}
	Line2D(MyVector2 p1, MyVector2 p2) :
		Shape2D(p1,p2,0.0f)
	{
	}
};

struct Sphere2D : public Shape2D
{
	Sphere2D(MyVector2 p, float radius) :
		Shape2D(p, radius)
	{

	}
};

#endif