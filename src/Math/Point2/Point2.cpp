#include "Point2.h"

// �R���X�g���N�^

Point2::Point2(int x, int y) :
	x(x), y(y)
{
}

//����

float Point2::Length() const
{
	return std::sqrt((float)(x*x + y*y));
}

//����

float Point2::Distance(const Point2 & other) const
{
	return (*this - other).Length();
}

//�s�X�n����

float Point2::ManhattanDistance(const Point2 & other) const
{
	return (float)(std::abs(x - other.x) + std::abs(y - other.y));
}

// �����Z
const Point2 Point2::operator + (const Point2& other) const
{
	return Point2(x + other.x, y + other.y);
}

// �����Z
const Point2 Point2::operator - (const Point2& other) const
{
	return Point2(x - other.x, y - other.y);
}
//��r
const bool Point2:: operator == (const Point2& other) const
{
	return ((x == other.x) && (y == other.y));
}
//��r
const bool Point2:: operator != (const Point2& other) const
{
	return !(*this == other);
}
