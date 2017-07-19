#include "Collision2D.h"

/// <summary>
/// 線と円の当たり判定
/// </summary>
/// <param name="circlePos">円の位置　重ならないように修正される</param>
/// <param name="circleRadius">円の半径</param>
/// <param name="linePos1">線分の始点</param>
/// <param name="linePos2">線分の終点</param>
/// <returns></returns>

bool Collision2D::Circle_Line(MyVector2 circlePos, float circleRadius, MyVector2 linePos1, MyVector2 linePos2, MyVector2 & ansCirclePos)
{
	MyVector2 v1 = circlePos - linePos1;//p1からの円までのベクトル
	MyVector2 v = linePos2 - linePos1;//線のベクトル

	float t = MyVector2::Dot(v1, v) / MyVector2::Dot(v, v);

	MyVector2 vt = v * t;
	MyVector2 vn = v1 - vt;

	//p1の外側か
	if (t<0)
	{
		//p1と円の当たり判定
		if (v1.Length() <= circleRadius)
		{
			ansCirclePos = linePos1 + (circleRadius * MyVector2::Normalize(vn));
			return true;
		}
	}
	else//p1の内側
	{
		if (t>1)//p2の外側
		{
			//p2の外側にある場合の処理
			MyVector2 v2 = circlePos - linePos2;
			if (t > 1 && v2.Length() <= circleRadius)
			{
				ansCirclePos = linePos2 + (circleRadius * MyVector2::Normalize(vn));
				return true;
			}
		}
		else//p1とp2の間の処理
		{
			//p1の外側にある場合の処理

			//p1p2の間の処理
			if ((t > 0 && t < 1) && vn.Length() <= circleRadius)
			{
				ansCirclePos = linePos1 + vt + (circleRadius * MyVector2::Normalize(vn));
				return true;
			}
		}
	}
	return false;
}

/// <summary>
/// 線と線の当たり判定
/// </summary>
/// <param name="p0">線分1の始点</param>
/// <param name="p1">線分1の終点</param>
/// <param name="p2">線分2の始点</param>
/// <param name="p3">線分2の終点</param>
/// <param name="I">交差座標を返す</param>
/// <returns></returns>

bool Collision2D::Line_Line(MyVector2 p0, MyVector2 p1, MyVector2 p2, MyVector2 p3, MyVector2 & I)
{
	MyVector2 a = p1 - p0;//線分1
	MyVector2 b = p3 - p2;//線分2

	MyVector2 c = p2 - p0;

	float t1 = (MyVector2::Cross(c, a) / MyVector2::Cross(a, b));
	if (0 > t1 || 1<t1) return false;

	float t2 = (MyVector2::Cross(c, b) / MyVector2::Cross(a, b));
	if (0 > t2 || 1<t2) return false;

	//交差座標を求める
	I = p0 + (t2 * a);
	return true;
}

bool Collision2D::Line_Line(Line2D l1, Line2D l2, MyVector2 & I)
{
	return Line_Line(l1.p1, l1.p2, l2.p1, l2.p2, I);
}

/// <summary>
/// カプセル型と円の当たり判定
/// </summary>
/// <param name="p1">カプセルの線分の始点</param>
/// <param name="p2">カプセルの線分の終点</param>
/// <param name="cp">円の位置</param>
/// <param name="r">カプセルの半径</param>
/// <param name="cr">円の半径</param>
/// <returns></returns>

bool Collision2D::Capsule_Circle(MyVector2 p1, MyVector2 p2, float r, MyVector2 cp, float cr)
{
	MyVector2 v = MyVector2();
	return Circle_Line(cp, cr + r, p1, p2, v);
}

/// <summary>
/// 線とカプセルの当たり判定
/// </summary>
/// <param name="p1"></param>
/// <param name="p2"></param>
/// <param name="r"></param>
/// <param name="lp1"></param>
/// <param name="lp2"></param>
/// <returns></returns>

bool Collision2D::Capsule_Line(MyVector2 p1, MyVector2 p2, float r, MyVector2 lp1, MyVector2 lp2, MyVector2 contactPos)
{
	if (Line_Line(p1, p2, lp1, lp2, contactPos)) return true;
	if (Circle_Line(p1, r, lp1, lp2, contactPos)) return true;
	if (Circle_Line(p2, r, lp1, lp2, contactPos)) return true;

	return false;
}

bool Collision2D::Capsule_Capsule(MyVector2 p1, MyVector2 p2, MyVector2 p3, MyVector2 p4, float r1, float r2)
{

	float radius = r1 + r2;

	return Capsule_Line(p1, p2, radius, p3, p4, MyVector2());
}

bool Collision2D::Circle_Ray(MyVector2 p1, MyVector2 p2, MyVector2 pc, float r)
{
	MyVector2 v = p2 - p1;//rayの方向
	MyVector2 v1 = p1 - pc;//円からrayの始点へのベクトル
	float b = MyVector2::Dot(v, v1);
	float c = b - r * r;
	float d = b * b - c;
	if (d >= 0)
	{
		//float t = -b - (float)Math.Sqrt(d);
		return true;
	}

	return false;
}

bool Collision2D::Square_Point(MyVector2 point, MyVector2 squareLeftUp, MyVector2 squareRightBottom)
{
	if (point.x > squareRightBottom.x || point.x < squareLeftUp.x) return false;
	if (point.y > squareRightBottom.y || point.y < squareLeftUp.y) return false;
	return true;
}
