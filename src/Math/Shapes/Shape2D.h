#ifndef	_SHAPE_2D_H_
#define	_SHAPE_2D_H_

#include"../Vector/MyVector2.h"
class Shape2D
{
public:
	Shape2D():
		p1(MyVector2()),
		p2(MyVector2()),
		radius(0.0f)
	{

	}
	Shape2D(MyVector2 p1, MyVector2 p2, float radius):
		p1(p1),
		p2(p2),
		radius(radius)
	{

	}
	Shape2D(MyVector2 p, float radius):
		Shape2D(p,p,radius)
	{

	}

	//à íuÇÃê›íË
	void Translate(MyVector2 vec)
	{
		p1 += vec;
		p2 += vec;
	}

public:
	MyVector2 p1;
	MyVector2 p2;
	float radius;
};

#endif