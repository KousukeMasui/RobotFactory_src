#include "Extrusion3D.h"
#include<cmath>
#include"Math/Shapes/3D/BoundingBox/BoundingBox3D.h"
#include"Math/Shapes/3D/Sphere/Sphere.h"
#include"Math/Shapes/3D/Line/Line3D.h"
MyVector3 Extrusion3D::Box_ExtrusionSphere(const MyVector3& SpherePos,float radius,const MyVector3& boxPos, const MyVector3& size, const MyVector3& contactPos)
{
	//四角の中心を回転軸にした時の座標
	MyVector3 otherPos = SpherePos - boxPos;
	MyVector3 cPos = contactPos - boxPos;

	MyVector3 toContactPos = cPos - otherPos;
	//交点までの距離がほぼ等しい場合 (中点が四角の内部の場合)
	if (toContactPos.Length() < FLT_EPSILON)
	{
		return MyVector3();
	}
	else//中点が離れている場合
	{
		return MyVector3();
	}

}

MyVector3 Extrusion3D::Box_ExtrusionSphere(const Sphere & sphere, const BoundingBox3D & box, const MyVector3 & contactPos, const MyVector3 & velocity)
{
	//1フレームの間の線を作成
	Line3D line(sphere.m_center, sphere.m_center - velocity);

	//線と立方体の交点を求める
	MyVector3 cPos = box.IsCollide(line).hitPosition;
	//どの方向の面に押し出されたか判定
	MyVector3 normal = box.CalcNormal(cPos, line.p2);

	return sphere.m_center + (normal * sphere.m_radius);
}

MyVector3 Extrusion3D::Box_ExtrusionSphere(const MyVector3 & spherePos, float radius,
	const MyVector3 & boxPos, const MyVector3& size, const MyMatrix4 & boxRotate, const MyVector3 & contactPos)
{
	//立方体を原点に移動した球の位置
	MyVector3 pos = spherePos - boxPos;
	//立方体を原点に移動した交点の位置
	MyVector3 cPos = contactPos - boxPos;
	//回転の逆行列を求める
	MyMatrix4 inverseRotate = MyMatrix4::InverseMatrix(boxRotate);
	//回転なしの場合の位置を求める
	pos = pos * inverseRotate;
	cPos = cPos * inverseRotate;

	//回転なしの場合の押し出し位置を求める
	MyVector3 p = Box_ExtrusionSphere(pos, radius, MyVector3(), size, cPos);
	
	//回転させる
	p = p * boxRotate;
	
	//原点から元の位置に戻す
	p += boxPos;

	return p;
}
