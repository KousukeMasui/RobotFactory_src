#include "ShapeRenderer.h"

#include<DxLib.h>
#include"Math/Converter.h"
#include"Math/Shapes/3D/Sphere/Sphere.h"
#include"Math/Shapes/3D/Capsule/Capsule.h"
#include"Math/Shapes/3D/BoundingBox/BoundingBox3D.h"
#include"Math/Shapes/3D/Line/Line3D.h"
#include"Math/Shapes/3D/Ray/Ray.h"
#include"Math/Shapes/3D/BoundingBox/BoundingBox3D.h"
#include"Model/Model/Model.h"
#include"Resources.h"
void ShapeRenderer::Draw(const Sphere & sphere)
{
	//球図形の描画
	DrawSphere3D(Converter::MyVector3ToVECTOR(sphere.m_center), sphere.m_radius, 16, GetColor(255, 0, 0), GetColor(255, 0, 0), true);
}

void ShapeRenderer::Draw(const Capsule & capsule)
{
	//カプセルの描画
	DrawCapsule3D(
		Converter::MyVector3ToVECTOR(capsule.m_line.m_start),
		Converter::MyVector3ToVECTOR(capsule.m_line.m_end),
		capsule.m_radius, 16, GetColor(255, 255, 0), GetColor(255, 255, 0), false);
}

void ShapeRenderer::Draw(const Line3D & line)
{
	//線の描画
	DrawLine3D(
		Converter::MyVector3ToVECTOR(line.m_start),
		Converter::MyVector3ToVECTOR(line.m_end),
		GetColor(255, 0, 0));
}

void ShapeRenderer::Draw(const Ray & ray)
{
	//rayの描画 先をfloatの最大値を掛けた最大の位置まで飛ばす
	DrawLine3D(
		Converter::MyVector3ToVECTOR(ray.m_position),
		Converter::MyVector3ToVECTOR(ray.m_position + ray.m_direction * FLT_MAX),
		GetColor(255, 0, 0));
}

void ShapeRenderer::Draw(const BoundingBox3D & box)
{
	Model model(MODEL_ID::BOX);

	model.Draw(box.m_center, box.GetSize(), box.m_rotate);
}
