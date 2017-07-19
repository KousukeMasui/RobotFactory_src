#ifndef	_MY_RECT_H_
#define	_MY_RECT_H_

class MyRect
{
public:
	MyRect(float left=0.0f, float top = 0.0f, float right = 0.0f, float bottom = 0.0f);

	static MyRect Lerp(const MyRect& begin, const MyRect& end, float rate);
public:
	float left;
	float top;
	float right;
	float bottom;
};

#endif