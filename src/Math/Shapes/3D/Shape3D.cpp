#include "Shape3D.h"

Shape3D::Shape3D() :
	p1(MyVector3()),
	p2(p1),
	radius(0.0f)
{

}

//ƒ|ƒŠƒSƒ“—p
Shape3D::Shape3D(const std::vector<MyVector3>& v) :
	Shape3D(MyVector3(), v)
{
}

Shape3D::Shape3D(const MyVector3 & p, const std::vector<MyVector3>& v) :
	p1(p),
	p2(p),
	radius(0.0f),
	vertices(v)
{
}

Shape3D::Shape3D(const MyVector3 & p1, const MyVector3 & p2, float radius) :
	p1(p1),
	p2(p2),
	radius(radius),
	size()
{
}

Shape3D::Shape3D(const MyVector3 & p, float radius) :
	p1(p),
	p2(p),
	radius(radius),
	size()
{
}

//ˆÊ’u‚Ìİ’è vertices‚ÍŒ»İ“®‚©‚µ‚Ä‚¢‚È‚¢

void Shape3D::Translate(const MyVector3 & vec)
{
	p1 += vec;
	p2 += vec;

	for (auto vertex : vertices)
	{
		vertex += vec;
	}
}
