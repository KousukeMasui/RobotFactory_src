#pragma once
#include<cmath>
// �Q�������W
struct Point2
{
	// �R���X�g���N�^
	Point2(int x = 0, int y = 0);
	//����
	float Length() const;
	//����
	float Distance(const Point2& other) const;
	//�s�X�n����
	float ManhattanDistance(const Point2& other) const;

	// �����Z
	const Point2 operator + (const Point2& other) const;

	// �����Z
	const Point2 operator - (const Point2& other) const;
	//��r
	const bool operator == (const Point2& other) const;
	//��r
	const bool operator != (const Point2& other) const;

	int x;	// x���W
	int y;	// y���W
};