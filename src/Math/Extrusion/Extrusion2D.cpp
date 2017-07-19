#include "Extrusion2D.h"
#include"Math\Collision\Collision2D.h"

MyVector2 Extrusion2D::Box_ExtrusionSphere(MyVector2 SpherePos, float radius, MyVector2 boxPos, std::vector<MyVector2> vertices, MyVector2 contactPos)
{
	//四角の中心を回転軸にした時の座標
	MyVector2 otherPos = SpherePos - boxPos;
	
	MyVector2 vec = MyVector2();
	//四角の外の場合正常に動くプログラム
	MyVector2 direction = otherPos-(contactPos - boxPos);//2点間の距離
	float length = direction.Length();
	float directionLength = radius - length;//めりこんだ長さ

	//四角の中にいたら
	if (length <= 0.01f)//Normalize防止
	{
		//direction = otherPos;
		for (int i = 0; i < vertices.size(); i++)
		{
			MyVector2 p1 = vertices[i];
			int v = (i + 1) % vertices.size();
			MyVector2 p2 = vertices[(i + 1) % vertices.size()];

			MyVector2 lineContactPos;
			if (Collision2D::Line_Line(boxPos, boxPos + (otherPos*100.0f), p1, p2, lineContactPos))
			{
  				direction = lineContactPos - boxPos;
				length = direction.Length();
				break;
			}
		}
		direction.Normalize();//正規化

		direction *= (length+radius);//めりこんだ長さのベクトルに
		MyVector2 p = boxPos + direction;
		return p;
	}
	direction.Normalize();//正規化

	direction *= directionLength;//めりこんだ長さのベクトルに

	MyVector2 p = otherPos + direction;

	p += boxPos;

	return p;
}
