#ifndef	 _BOUNDING_BOX_3D_H_
#define	 _BOUNDING_BOX_3D_H_

#include"Math/Vector/MyVector3.h"
#include"Math/Matrix/MyMatrix4.h"
#include<vector>
#include"Math/Collision/HitInfo/HitInfo.h"
struct Sphere;
struct Line3D;
struct Ray;
struct Capsule;
enum class VertexIndices//頂点の列挙
{
	MIN = 0,
	MIN_MIN_MAX,
	MIN_MAX_MIN,
	MIN_MAX_MAX,
	MAX_MIN_MIN,
	MAX_MIN_MAX,
	MAX_MAX_MIN,
	MAX,

	COUNT = 8//合計個数
};
struct BoundingBox3D
{
	BoundingBox3D(const MyVector3& min, const MyVector3& max,const MyVector3& center);
	BoundingBox3D(const MyVector3& center, const MyVector3& size, const MyMatrix4& rotate);
	~BoundingBox3D();
	void Rotate(const MyMatrix4& rotate);

	//頂点座標を取得
	MyVector3 GetVertexPosition(VertexIndices vertex) const;
	std::vector<MyVector3> GetVertexPositions() const;
	//回転なしの頂点座標
	MyVector3 GetNonRotateVertexPosition(VertexIndices vertex) const;
	std::vector<MyVector3> GetNonRotateVertexPositions(VertexIndices vertex) const;
	//サイズを取得
	MyVector3 GetSize() const;

	bool IsInside(const MyVector3& position) const;
	//当たり判定
	HitInfo IsCollide(const Sphere& sphere) const;
	HitInfo IsCollide(const Capsule& capsule) const;
	HitInfo IsCollide(const Line3D& line) const;
	HitInfo IsCollide(const Ray& ray) const;
	HitInfo IsCollideRotate(const Line3D& line) const;
	HitInfo IsCollideRotate(const Capsule& Capsule) const;
	HitInfo IsCollideRotate(const Ray& ray) const;

	//どの面の方向かを調べてその法線を返す
	MyVector3 CalcNormal(const MyVector3& contactPos,const MyVector3& prevPos) const;
	//中心座標
	MyVector3 m_center;
	//頂点座標
	std::vector<MyVector3> m_vertices;
	//回転行列
	MyMatrix4 m_rotate;
};

#endif