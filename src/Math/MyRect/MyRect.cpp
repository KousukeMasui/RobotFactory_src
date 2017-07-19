#include "MyRect.h"
#include"../MyMath.h"
MyRect::MyRect(float left, float top, float right, float bottom):
	left(left),
	top(top),
	right(right),
	bottom(bottom)
{
}

MyRect MyRect::Lerp(const MyRect & begin, const MyRect & end, float rate)
{
	return MyRect(
		MyMath::Lerp(begin.left, end.left, rate),
		MyMath::Lerp(begin.top, end.top, rate),
		MyMath::Lerp(begin.right, end.right, rate),
		MyMath::Lerp(begin.bottom, end.bottom, rate));
}
