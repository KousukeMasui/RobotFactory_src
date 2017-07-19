#pragma once
#include<cmath>
// ‚QŸŒ³À•W
struct Point2
{
	// ƒRƒ“ƒXƒgƒ‰ƒNƒ^
	Point2(int x = 0, int y = 0);
	//’·‚³
	float Length() const;
	//‹——£
	float Distance(const Point2& other) const;
	//sŠX’n‹——£
	float ManhattanDistance(const Point2& other) const;

	// ‘«‚µZ
	const Point2 operator + (const Point2& other) const;

	// ‘«‚µZ
	const Point2 operator - (const Point2& other) const;
	//”äŠr
	const bool operator == (const Point2& other) const;
	//”äŠr
	const bool operator != (const Point2& other) const;

	int x;	// xÀ•W
	int y;	// yÀ•W
};