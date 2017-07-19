#ifndef	  _COLLISION_3D_H_
#define	  _COLLISION_3D_H_

#include"../Vector/MyVector3.h"
#include"../Vector/MyVector2.h"
#include"../Matrix/MyMatrix4.h"
#include<vector>
#include"../Shapes/3D/Shape3D.h"
#include"../Shapes\Shapes.h"
#include"Math/Converter.h"
#include"Model/StaticModel/StaticModel.h"


struct Sphere;
struct BoundingBox3D;
struct Line3D;
struct Capsule;
#include"HitInfo/HitInfo.h"

class Collision3D
{
public:

	/// <summary>
	/// 線と球の当たり判定 押し出しあり
	/// </summary>
	/// <param name="p1">線の始点</param>
	/// <param name="p2">線の終点</param>
	/// <param name="radius">半径</param>
	/// <param name="circlePos">球の位置</param>
	/// <param name="contactMyVector3">接点</param>
	/// <returns></returns>
	static bool Line_Sphere_Extrusion(const MyVector3& p1,const MyVector3& p2, float radius, MyVector3& circlePos, MyVector3& contactPoint);
	//押し出しなし
	static bool Line_Sphere(const MyVector3& p1, const MyVector3& p2, float radius,const MyVector3& circlePos,MyVector3& contactPoint);

	
	//rayと球の当たり判定
	static bool Ray_Sphere(const MyVector3& rayPos, const MyVector3& direction, const MyVector3& spherePos, float radius, float &t, MyVector3 &q);
	
	/// <summary>
	/// 球体とカプセル型の当たり判定
	/// </summary>
	/// <param name="p1">カプセルの始点</param>
	/// <param name="p2">カプセルの終点</param>
	/// <param name="circlePos">球体の位置</param>
	/// <param name="r1">カプセルの半径</param>
	/// <param name="r2">球体の半径</param>
	/// <returns></returns>
	static bool Capsule_BoundarySphere(MyVector3 p1, MyVector3 p2, MyVector3& circlePos, float r1, float r2, MyVector3& contactMyVector3);

	/// <summary>
	/// 壁と動体の反射処理
	/// </summary>
	/// <param name="velocity">動体の移動量</param>
	/// <param name="normal">壁の法線ベクトル</param>
	/// <param name="e">反発係数</param>
	static void Reflection(MyVector3& velocity, MyVector3 normal, float e);

	/// <summary>
	/// 動体同士の反射処理
	/// </summary>
	/// <param name="velocity1">動体1の方向ベクトル</param>
	/// <param name="position1">動体1の位置</param>
	/// <param name="radius1">動体1の半径</param>
	/// <param name="velocity2">動体2の方向ベクトル</param>
	/// <param name="position2">動体2の位置</param>
	/// <param name="radius2">動体2の半径</param>
	/// <param name="e">反発係数</param>
	/// <param name="massRaito">質量比</param>
	static void Reflection(
		MyVector3& velocity1,MyVector3& position1, float radius1,
		MyVector3& velocity2,MyVector3& position2, float radius2,
		float e,
		float massRaito);

	static bool Capsule_Capsule(MyVector3 p1, MyVector3 p2, float r1, MyVector3 p3, MyVector3 p4, float r2);

	// 与えられた点pに対して、AABB bの上もしくは中にあるpの最近接点qを返す
	static void ClosestPtPointAABB(MyVector3 position, MyVector3 boxPos,MyVector3 boxSize, MyVector3 &qPos)
	{
		float p[3];
		p[0] = position.x;
		p[1] = position.y;
		p[2] = position.z;
		float q[3];

		float min[3];
		min[0] = boxPos.x - boxSize.x;
		min[1] = boxPos.y - boxSize.y;
		min[2] = boxPos.z - boxSize.z;
		float max[3];
		max[0] = boxPos.x + boxSize.x;
		max[1] = boxPos.y + boxSize.y;
		max[2] = boxPos.z + boxSize.z;

		// 各座標軸に対して、点の座標値が箱の外側にある場合に
		// 箱まで点をクランプ、そうでなければそのまま
		for (int i = 0; i < 3; i++) {
			float v = p[i];
			if (v < min[i]) v = min[i]; // v = max(v, b.min[i])
			if (v > max[i]) v = max[i]; // v = min(v, b.max[i])
			q[i] = v;
		}

		qPos = MyVector3(q[0], q[1], q[2]);
	}

	// 与えられた点pに対して、OBB bの上(もしくは中)にあるpの最近接点qを返す
	static void ClosestPtPointOBB(const MyVector3& p, const MyVector3& boxPos, const MyMatrix4& boxRotate, const MyVector3& boxSize, MyVector3 &q);

	// 球sがOBB bに交差している場合は真を返し、そうでなければ偽を返す
	// 球の中心に対するOBB上の最近接点である点pも返す
	static bool TestSphereOBB(const MyVector3& spherePos, float sphereRadius, const MyVector3& boxPos, const MyMatrix4& boxRotate, const MyVector3& boxSize, MyVector3 &p);


};

#endif