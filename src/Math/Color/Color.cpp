#include "Color.h"
#include"Math/MyMath.h"
const Color Color::Black(0.0f, 0.0f, 0.0f, 1.0f);
const Color Color::White(1.0f, 1.0f, 1.0f, 1.0f);

Color::Color(float r, float g, float b, float a):
	r(r),g(g),b(b),a(a)
{
}

Color Color::Min(const Color & value1, const Color & value2)
{
	return Color(
		MyMath::Min(value1.r, value2.r),
		MyMath::Min(value1.g, value2.g),
		MyMath::Min(value1.b, value2.b),
		MyMath::Min(value1.a, value2.a));
}

Color Color::Max(const Color & value1, const Color & value2)
{
	return Color(
		MyMath::Max(value1.r, value2.r),
		MyMath::Max(value1.g, value2.g),
		MyMath::Max(value1.b, value2.b),
		MyMath::Max(value1.a, value2.a));
}

Color Color::Clamp(const Color & value1, const Color & min, const Color & max)
{
	return Color(
		MyMath::Clamp(value1.r, min.r,max.r),
		MyMath::Clamp(value1.g, min.r,max.r),
		MyMath::Clamp(value1.b, min.r,max.r),
		MyMath::Clamp(value1.a, min.r,max.r));
}

Color & operator+=(Color & c1, const Color & c2)
{
	c1.r += c2.r;
	c1.g += c2.g;
	c1.b += c2.b;
	c1.a += c2.a;
	return c1;
}

Color & operator-=(Color & c1, const Color & c2)
{
	c1.r -= c2.r;
	c1.g -= c2.g;
	c1.b -= c2.b;
	c1.a -= c2.a;
	return c1;
}

Color & operator*=(Color & c1, const Color & c2)
{
	c1.r *= c2.r;
	c1.g *= c2.g;
	c1.b *= c2.b;
	c1.a *= c2.a;
	return c1;
}

Color & operator*=(Color & c, float s)
{
	c.r *= s;
	c.g *= s;
	c.b *= s;
	c.a *= s;
	return c;
}

Color & operator/=(Color & c, float s)
{
	c.r /= s;
	c.g /= s;
	c.b /= s;
	c.a /= s;
	return c;
}

Color operator+(Color c1, const Color & c2)
{
	return c1 += c2;
}

Color operator-(Color c1, const Color & c2)
{
	return c1 -= c2;
}

Color operator*(Color c1, const Color & c2)
{
	return c1 *= c2;
}

Color operator*(Color c, float s)
{
	return c *=s;
}

Color operator*(float s, Color c)
{
	return c *= s;
}

Color operator/(Color c, float s)
{
	return c /= s;
}
