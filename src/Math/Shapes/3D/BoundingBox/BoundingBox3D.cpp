#include "BoundingBox3D.h"
#include"Math/Converter.h"
#include"Math/Matrix/MyMatrix4.h"
#include"Math/Matrix/MyQuaternion.h"
#include"Math/MyMath.h"
#include"Math/Shapes/3D/Sphere/Sphere.h"
#include"Math/Shapes/3D/Line/Line3D.h"
#include"Math/Shapes/3D/Ray/Ray.h"
#include"Math/Shapes/3D/Capsule/Capsule.h"
BoundingBox3D::BoundingBox3D(const MyVector3 & min, const MyVector3 & max, const MyVector3& center):
	m_center(center),
	m_rotate(MyMatrix4::Identity())
{
	//centerを除外した頂点を求める
	m_vertices.resize(8);

	m_vertices[(int)VertexIndices::MIN] = min;
	m_vertices[(int)VertexIndices::MIN_MIN_MAX] = MyVector3(min.x, min.y, max.z);
	m_vertices[(int)VertexIndices::MIN_MAX_MIN] = MyVector3(min.x, max.y, min.z);
	m_vertices[(int)VertexIndices::MIN_MAX_MAX] = MyVector3(min.x, max.y, max.z);
	m_vertices[(int)VertexIndices::MAX_MIN_MIN] = MyVector3(max.x, min.y, min.z);
	m_vertices[(int)VertexIndices::MAX_MIN_MAX] = MyVector3(max.x, min.y, max.z);
	m_vertices[(int)VertexIndices::MAX_MAX_MIN] = MyVector3(max.x, max.y, min.z);
	m_vertices[(int)VertexIndices::MAX] = max;
}

BoundingBox3D::BoundingBox3D(const MyVector3 & center, const MyVector3 & size, const MyMatrix4 & rotate):
	BoundingBox3D(center - size / 2.0f, center +size / 2.0f,center)
{
	m_rotate = rotate;
}

BoundingBox3D::~BoundingBox3D()
{
}

void BoundingBox3D::Rotate(const MyMatrix4 & rotate)
{
	m_rotate = rotate;
}

MyVector3 BoundingBox3D::GetVertexPosition(VertexIndices vertex) const
{
	return (m_vertices[(int)vertex]  * m_rotate)+ m_center;
}

std::vector<MyVector3> BoundingBox3D::GetVertexPositions() const
{
	std::vector<MyVector3> result;
	for (int i = 0; i < 8; i++)
	{
		result.push_back(GetVertexPosition((VertexIndices)i));
	}

	return result;
}

MyVector3 BoundingBox3D::GetNonRotateVertexPosition(VertexIndices vertex) const
{
	return m_vertices[(int)vertex] + m_center;
}

std::vector<MyVector3> BoundingBox3D::GetNonRotateVertexPositions(VertexIndices vertex) const
{
	std::vector<MyVector3> result;
	for (int i = 0; i < 8; i++)
	{
		result.push_back(GetNonRotateVertexPosition((VertexIndices)i));
	}

	return result;
}

MyVector3 BoundingBox3D::GetSize() const
{
	return m_vertices[(int)VertexIndices::MAX] - m_vertices[(int)VertexIndices::MIN];
}

bool BoundingBox3D::IsInside(const MyVector3 & position) const
{
	MyVector3 min = GetVertexPosition(VertexIndices::MIN);
	MyVector3 max = GetVertexPosition(VertexIndices::MAX);
	return min.x <= position.x && max.x>= position.x &&
		min.y <= position.y && max.y >= position.y &&
		min.z <= position.z && max.z >= position.z;
}

HitInfo BoundingBox3D::IsCollide(const Sphere & sphere) const
{
	HitInfo hit;
	hit.hitPosition = MyMath::Clamp(sphere.m_center, GetNonRotateVertexPosition(VertexIndices::MIN), GetNonRotateVertexPosition(VertexIndices::MAX));
	hit.isHit = MyVector3::Distance(hit.hitPosition, sphere.m_center) <= sphere.m_radius;
	return hit;
}

HitInfo BoundingBox3D::IsCollide(const Capsule & capsule) const
{
	HitInfo hit;
	MyVector3 direction = capsule.m_line.Direction();
	float length = direction.Length();
	direction.Normalize();
	HitInfo rayHit = IsCollide(Ray(capsule.m_line.m_start, direction));
	//ここが半径を想定していない為カプセルの中央線に触れるまで判定されない
	if (rayHit.isHit)
	{
		rayHit.t /= length;
		//p1よりも下の場合
		if (rayHit.t <= 0.0f)
		{
			return IsCollide(Sphere(capsule.m_line.m_start, capsule.m_radius));
		}
		else if (rayHit.t >= 1.0f)//p2
		{
			return IsCollide(Sphere(capsule.m_line.m_end, capsule.m_radius));
		}
		else
		{
			float t;
			return Sphere(hit.hitPosition, capsule.m_radius).IsCollide(capsule.m_line,t);
		}
	}
	return hit;
}

HitInfo BoundingBox3D::IsCollide(const Line3D & line) const
{
	float length = line.Length();
	HitInfo hit = IsCollide(Ray(line.m_start, line.Direction()));
	if (hit.isHit)
	{
		hit.t /= length;
		//線の外側の場合
		if (hit.t<0.0f || hit.t >1.0f)
		{
			hit.isHit = false;
			return hit;
		}

		hit.hitPosition = line.m_start + MyVector3::Normalize(line.Direction()) * length * hit.t;
	}
	return hit;
}

HitInfo BoundingBox3D::IsCollide(const Ray & ray) const
{
	HitInfo hit;
	float tmin = 0.0f;          // -FLT_MAXに設定して直線における最初の交差を得る
	float tmax = FLT_MAX; // (線分に対して)光線が移動することのできる最大の距離に設定
	
	float p[3];
	p[0] = ray.m_position.x;
	p[1] = ray.m_position.y;
	p[2] = ray.m_position.z;

	float d[3];
	d[0] = ray.m_direction.x;
	d[1] = ray.m_direction.y;
	d[2] = ray.m_direction.z;
	MyVector3 boxSize = GetSize();
	//四角の面の最低値
	float min[3];
	min[0] = m_center.x - boxSize.x / 2.0f;
	min[1] = m_center.y - boxSize.y / 2.0f;
	min[2] = m_center.z - boxSize.z / 2.0f;

	//四角の面の最大値
	float max[3];
	max[0] = m_center.x + boxSize.x / 2.0f;
	max[1] = m_center.y + boxSize.y / 2.0f;
	max[2] = m_center.z + boxSize.z / 2.0f;

	//EPSILON 微小な誤差　許容範囲
	// 3つのすべてスラブに対して
	for (int i = 0; i < 3; i++) {
		if (std::abs(d[i]) < FLT_EPSILON)
		{
			// 光線はスラブに対して平行。原点がスラブの中になければ交差なし
			if (p[i] < min[i] || p[i] > max[i]) return hit;
		}
		else
		{
			// スラブの近い平面および遠い平面と交差する光線のtの値を計算
			float ood = 1.0f / d[i];
			float t1 = (min[i] - p[i]) * ood;
			float t2 = (max[i] - p[i]) * ood;
			// t1が近い平面との交差、t2が遠い平面との交差となる
			if (t1 > t2) std::swap(t1, t2);
			// スラブの交差している間隔との交差を計算
			if (t1 > tmin) tmin = t1;
			if (t2 < tmax) tmax = t2;
			// スラブに交差がないことが分かれば衝突はないのですぐに終了
			if (tmin > tmax)
			{
				return hit;
			}
		}
	}
	//if (!isHit) return false;

	hit.isHit = true;
	// 光線が3つのスラブすべてに交差している。点(q)と交差のtの値(tmin)を返す
	hit.hitPosition = ray.m_position + ray.m_direction * tmin;
	hit.t = tmin;
	return hit;
}

HitInfo BoundingBox3D::IsCollideRotate(const Line3D & line) const
{
	HitInfo hit;
	MyMatrix4 inv = MyMatrix4::InverseMatrix(m_rotate);
	//boxの位置が0でかつ回転していない場合のローカル位置の線分を作成
	Line3D invLine = Line3D((line.m_start - m_center) * inv, (line.m_end - m_center) * inv);

	hit = IsCollide(invLine);
	if (hit.isHit)
	{
		hit.hitPosition = (hit.hitPosition * m_rotate) + m_center;
	}
	return hit;
}

HitInfo BoundingBox3D::IsCollideRotate(const Capsule & capsule) const
{
	HitInfo hit;
	MyMatrix4 inv = MyMatrix4::InverseMatrix(m_rotate);
	Capsule invCapsule =Capsule( Line3D((capsule.m_line.m_start - m_center) * inv + m_center, (capsule.m_line.m_end - m_center) * inv + m_center),capsule.m_radius);
	BoundingBox3D box = *this;
	box.m_center = MyVector3::Zero();
	hit = box.IsCollide(invCapsule);
	if (hit.isHit)
	{
		hit.hitPosition = (hit.hitPosition * m_rotate) + m_center;
	}
	return hit;
}

HitInfo BoundingBox3D::IsCollideRotate(const Ray & ray) const
{
	MyMatrix4 invRotate = MyMatrix4::InverseMatrix(m_rotate);

	MyVector3 rPos = (ray.m_position-m_center) * invRotate;
	MyVector3 direction = (ray.m_direction) * invRotate;

	HitInfo hit = IsCollide(Ray(rPos + m_center, direction));
	if (hit.isHit)
	{
		hit.hitPosition *= MyMatrix4(m_rotate).SetPosition(m_center);
	}
	return hit;
}

MyVector3 BoundingBox3D::CalcNormal(const MyVector3& contactPos, const MyVector3& prevPos) const
{
	MyVector3 leftUpFront = GetVertexPosition(VertexIndices::MIN);
	MyVector3 rightBottomBack = GetVertexPosition(VertexIndices::MAX);

	MyVector3 result;
	//前の位置がleft壁より外の場合
	if (leftUpFront.x >= prevPos.x)
	{
		result.x = -1;
	}
	else if(rightBottomBack.x <= prevPos.x)//右より外
	{
		result.x = 1;
	}
	//Y
	if (leftUpFront.y >= prevPos.y)
	{
		result.y = -1;
	}
	else if (rightBottomBack.y <= prevPos.y)//右より外
	{
		result.y = 1;
	}
	//Z
	if (leftUpFront.z >= prevPos.z)
	{
		result.z = -1;
	}
	else if (rightBottomBack.z <= prevPos.z)//右より外
	{
		result.z = 1;
	}
	return result.Normalize();
}
