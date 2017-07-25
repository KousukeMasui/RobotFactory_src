#include "Collision3D.h"
#include "../Shapes/3D/BoundingBox/BoundingBox3D.h"
#include"../MyMath.h"

#include"../Shapes/3D/Sphere/Sphere.h"
#include"../Shapes/3D/Capsule/Capsule.h"

bool Collision3D::Line_Sphere(const MyVector3 & p1, const MyVector3 & p2, float radius, const MyVector3 & circlePos, MyVector3 & contactPoint)
{
	MyVector3 v = p2 - p1;//線の方向ベクトル
	MyVector3 v1 = circlePos - p1;//始点から球体への方向ベクトル

	float t = MyVector3::Dot(v, v1) / MyVector3::Dot(v, v);

	MyVector3 vt = t * v;
	MyVector3 vn = v1 - vt;

	//p1の外側か
	if (0 < t && v1.Length() < radius)
	{
		contactPoint = p1;
		return true;
	}
	MyVector3 v2 = circlePos - p2;
	if (t > 1 && v2.Length() < radius)//v2より外側
	{
		contactPoint = p2;
		return true;
	}
	if ((0 < t && t < 1) && vn.Length() < radius)
	{
		MyVector3 vr = MyVector3::Normalize(vn) * radius;
		contactPoint = p1 + vt;
		return true;
	}
	return false;
}

bool Collision3D::Ray_Sphere(const MyVector3 & rayPos, const MyVector3 & direction, const MyVector3 & spherePos, float radius, float & t, MyVector3 & q)
{
	MyVector3 m = rayPos - spherePos;
	float b = MyVector3::Dot(m, direction);
	float c = MyVector3::Dot(m, m) - radius * radius;
	// rの原点がsの外側にあり(c > 0)、rがsから離れていく方向を指している場合(b > 0)に終了
	if (c > 0.0f && b > 0.0f) return false;
	float discr = b*b - c;
	// 負の判別式は光線が球を外れていることに一致
	if (discr < 0.0f) return false;
	// これで光線は球と交差していることが分かり、交差する最小の値tを計算
	t = -b - std::sqrt(discr);
	// tが負である場合、光線は球の内側から開始しているのでtをゼロにクランプ
	if (t < 0.0f) t = 0.0f;
	q = rayPos + t * direction;
	return true;
}

/// <summary>
/// 球体とカプセル型の当たり判定
/// </summary>
/// <param name="p1">カプセルの始点</param>
/// <param name="p2">カプセルの終点</param>
/// <param name="circlePos">球体の位置</param>
/// <param name="r1">カプセルの半径</param>
/// <param name="r2">球体の半径</param>
/// <returns></returns>

bool Collision3D::Capsule_BoundarySphere(MyVector3 p1, MyVector3 p2, MyVector3 & circlePos, float r1, float r2, MyVector3 & contactPoint)
{
	return Line_Sphere(p1, p2, r1 + r2, circlePos, contactPoint);
}
/// <summary>
/// 壁と動体の反射処理
/// </summary>
/// <param name="velocity">動体の移動量</param>
/// <param name="normal">壁の法線ベクトル</param>
/// <param name="e">反発係数</param>

void Collision3D::Reflection(MyVector3 & velocity, MyVector3 normal, float e)
{
	MyVector3 vn = -MyVector3::Dot(velocity, normal) * normal;
	MyVector3 vt = velocity + vn;
	velocity = vn * e + vt;
}

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

void Collision3D::Reflection(MyVector3 & velocity1, MyVector3 & position1, float radius1, MyVector3 & velocity2, MyVector3 & position2, float radius2, float e, float massRaito)
{
	//物体の中心を結んだ方向ベクトル
	MyVector3 n = MyVector3::Normalize(position2 - position1);

	//物体1の進む方向　中心方向n　接線方向t
	MyVector3 v1n = MyVector3::Dot(velocity1, n) * n;
	MyVector3 v1t = velocity1 - v1n;

	//物体2の進む方向　中心方向n　接線方向t
	MyVector3 v2n = MyVector3::Dot(velocity2, n) * n;
	MyVector3 v2t = velocity2 - v1n;

	//質量比と反発を考えた反発
	velocity1 = (v2n - v1n) * (1 + e) / (massRaito + 1) + velocity1;
	velocity2 = (v1n - v2n) * (1 + e) / (1 / massRaito + 1) + velocity2;
}

bool Collision3D::Capsule_Capsule(MyVector3 p1, MyVector3 p2, float r1, MyVector3 p3, MyVector3 p4, float r2)
{
	MyVector3 a = p2 - p1;//線分1の方向ベクトル
	MyVector3 b = p4 - p3;//線分2の方向ベクトル
	MyVector3 c = p3 - p1;

	MyVector3 n = MyVector3::Cross(a, b);

	MyVector3 N = MyVector3::Normalize(n);
	float L = MyVector3::Dot(c, N);

	MyVector3 n1 = MyVector3::Cross(a, N);
	MyVector3 n2 = MyVector3::Cross(b, N);

	MyVector3 P3 = p3 - N * L;
	MyVector3 P4 = p4 - N * L;

	MyVector3 v1 = p1 - P3;
	MyVector3 v2 = p2 - P3;
	MyVector3 v3 = P3 - p1;
	MyVector3 v4 = P4 - p1;

	float L1 = MyVector3::Dot(v1, n2);
	float L2 = MyVector3::Dot(v2, n2);
	float L3 = MyVector3::Dot(v3, n1);
	float L4 = MyVector3::Dot(v4, n1);

	float t1 = L3 / (L3 - L4);
	float t2 = L1 / (L1 - L2);

	//p1とp2の内側の場合
	if ((t1 > 0 && t1 < 1) && (t2 > 0 && t2 < 1) && (std::abs(L) < r1 + r2))
	{
		MyVector3 vd = (N * (r1 + r2)*std::signbit(L));//押し出す量

		p3 = P3 + vd;
		p4 = P4 + vd;

		return true;
	}

	//p　引数のいらない部分の変数     pp 当たり判定の押し出し前の位置
	MyVector3 p, pp;
	p = MyVector3::Zero();
	pp = p1;//移動前のp1を保存
			//p1より外側の場合
	if (t1 < 0 && Capsule_BoundarySphere(p3, p4, p1, r1, r2, p))
	{
		return true;
	}
	//p2より外側の場合
	else if (t1> 0 && Capsule_BoundarySphere(p3, p4, p2, r1, r2, p))
	{
		return true;
	}
	return false;
}


void Collision3D::ClosestPtPointOBB(const MyVector3 & p, const MyVector3 & boxPos, const MyMatrix4 & boxRotate, const MyVector3 & boxSize, MyVector3 & q)
{
	MyVector3 d = p - boxPos;
	// 箱の中心における結果から開始、そこから段階的に進める
	q = boxPos;

	MyVector3 u[3];
	u[0] = boxRotate.GetLeft();
	u[1] = boxRotate.GetTop();
	u[2] = boxRotate.GetForward();

	float size[3];
	size[0] = boxSize.x;
	size[1] = boxSize.y;
	size[2] = boxSize.z;

	// 各OBBの軸に対して...
	for (int i = 0; i < 3; i++) {
		// dをその軸に射影して
		// 箱の中心からdの軸に沿った距離を得る
		float dist = MyVector3::Dot(d, u[i]);
		// 箱の範囲よりも距離が大きい場合、箱までクランプ
		if (dist > size[i]) dist = size[i];
		if (dist < -size[i]) dist = -size[i];
		// ワールド座標を得るためにその距離だけ軸に沿って進める
		q += dist * u[i];
	}
}

bool Collision3D::TestSphereOBB(const MyVector3 & spherePos, float sphereRadius, const MyVector3 & boxPos, const MyMatrix4 & boxRotate, const MyVector3 & boxSize, MyVector3 & p)
{
	// 球の中心に対する最近接点であるOBB上にある点pを見つける
	ClosestPtPointOBB(spherePos, boxPos, boxRotate, boxSize, p);

	// 球とOBBが交差するのは、球の中心から点pまでの(平方した)距離が
	// (平方した)球の半径よりも小さい場合
	MyVector3 v = p - spherePos;
	return v.Length() <= sphereRadius;
}