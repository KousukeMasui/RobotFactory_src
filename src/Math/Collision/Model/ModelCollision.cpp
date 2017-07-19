#include "ModelCollision.h"
#include<DxLib.h>
#include"../../Converter.h"
#include"Model/StaticModel/StaticModel.h"
#include"../../Shapes/3D/Line/Line3D.h"
#include"Math/Shapes/3D/Sphere/Sphere.h"
HitInfo ModelCollision::Model_Line3D(const StaticModel & model, const MyVector3 & p1, const MyVector3 & p2)
{
	MV1_COLL_RESULT_POLY  result = MV1CollCheck_Line(model.GetModelID(), -1, Converter::MyVector3ToVECTOR(p1), Converter::MyVector3ToVECTOR(p2));
	HitInfo hitInfo;
	hitInfo.isHit = (result.HitFlag == 1);
	hitInfo.normal = Converter::VECTORToMyVector3(result.Normal);
	hitInfo.hitPosition = Converter::VECTORToMyVector3(result.HitPosition);
	return hitInfo;
}

HitInfo ModelCollision::Model_Line3D(const StaticModel & model, const Line3D & line)
{
	return Model_Line3D(model, line.m_start, line.m_end);
}

HitInfo ModelCollision::Model_Sphere(const StaticModel & model, const Sphere &sphere)
{
	HitInfo hit;
	MV1_COLL_RESULT_POLY_DIM  dim_result = MV1CollCheck_Sphere(model.GetModelID(), -1, Converter::MyVector3ToVECTOR(sphere.m_center), sphere.m_radius);
	//当たっているポリゴンがない場合
	if (dim_result.HitNum <= 0)
	{
		//falseにして当たり判定の結果を開放する
		hit.isHit = false;
		MV1CollResultPolyDimTerminate(dim_result);
		return hit;
	}
	MyVector3 hitPosition,normal;
	for (int i = 0; i < dim_result.HitNum; i++)
	{
		MV1_COLL_RESULT_POLY r = MV1CollCheck_GetResultPoly(dim_result, i);
		hit.hitPosition += Converter::VECTORToMyVector3(r.HitPosition);
		hit.normal += Converter::VECTORToMyVector3(r.Normal);
	}
	hit.hitPosition /= dim_result.HitNum;
	hit.normal.Normalize();

	hit.isHit = true;
	MV1CollResultPolyDimTerminate(dim_result);
	return hit;
}

HitInfo ModelCollision::Model_Capsule(const StaticModel & model, const MyVector3 & p1, const MyVector3 & p2, float radius)
{
	HitInfo hit;
	MV1_COLL_RESULT_POLY_DIM resultDim = MV1CollCheck_Capsule(model.GetModelID(), -1, Converter::MyVector3ToVECTOR(p1), Converter::MyVector3ToVECTOR(p2), radius);
	hit.isHit = resultDim.HitNum > 0;//一つ以上のポリゴンと触れていたらtrue
	if (!hit.isHit)//当たっていない場合 終了
	{
		MV1CollResultPolyDimTerminate(resultDim);
		return hit;
	}
	//適当なポリゴンのnormalを保存して返す
	MV1_COLL_RESULT_POLY result = MV1CollCheck_GetResultPoly(resultDim, 0);
	hit.normal = Converter::VECTORToMyVector3(result.Normal);

	MV1CollResultPolyDimTerminate(resultDim);
	return hit;
}
