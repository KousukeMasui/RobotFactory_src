#include"../Vector/MyVector2.h"

#include"../Shapes\Shapes.h"

class Collision2D
{
public:
	/// <summary>
	/// 線と円の当たり判定
	/// </summary>
	/// <param name="circlePos">円の位置　重ならないように修正される</param>
	/// <param name="circleRadius">円の半径</param>
	/// <param name="linePos1">線分の始点</param>
	/// <param name="linePos2">線分の終点</param>
	/// <returns></returns>
	static bool Circle_Line(MyVector2 circlePos, float circleRadius, MyVector2 linePos1, MyVector2 linePos2, MyVector2& ansCirclePos);

	/// <summary>
	/// 線と線の当たり判定
	/// </summary>
	/// <param name="p0">線分1の始点</param>
	/// <param name="p1">線分1の終点</param>
	/// <param name="p2">線分2の始点</param>
	/// <param name="p3">線分2の終点</param>
	/// <param name="I">交差座標を返す</param>
	/// <returns></returns>
	static bool Line_Line(MyVector2 p0, MyVector2 p1, MyVector2 p2, MyVector2 p3, MyVector2& I);

	static bool Line_Line(Line2D l1, Line2D l2, MyVector2& I);
	/// <summary>
	/// カプセル型と円の当たり判定
	/// </summary>
	/// <param name="p1">カプセルの線分の始点</param>
	/// <param name="p2">カプセルの線分の終点</param>
	/// <param name="cp">円の位置</param>
	/// <param name="r">カプセルの半径</param>
	/// <param name="cr">円の半径</param>
	/// <returns></returns>
	static bool Capsule_Circle(MyVector2 p1, MyVector2 p2, float r, MyVector2 cp, float cr);

	/// <summary>
	/// 線とカプセルの当たり判定
	/// </summary>
	/// <param name="p1"></param>
	/// <param name="p2"></param>
	/// <param name="r"></param>
	/// <param name="lp1"></param>
	/// <param name="lp2"></param>
	/// <returns></returns>
	static bool Capsule_Line(MyVector2 p1, MyVector2 p2, float r, MyVector2 lp1, MyVector2 lp2, MyVector2 contactPos);

	static bool Capsule_Capsule(MyVector2 p1, MyVector2 p2, MyVector2 p3, MyVector2 p4, float r1, float r2);

	static bool Circle_Ray(MyVector2 p1, MyVector2 p2, MyVector2 pc, float r);


	static bool Square_Point(MyVector2 point, MyVector2 squareLeftUp, MyVector2 squareRightBottom);
};