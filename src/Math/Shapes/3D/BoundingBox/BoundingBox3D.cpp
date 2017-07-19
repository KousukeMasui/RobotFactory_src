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
	//center�����O�������_�����߂�
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
	//���������a��z�肵�Ă��Ȃ��׃J�v�Z���̒������ɐG���܂Ŕ��肳��Ȃ�
	if (rayHit.isHit)
	{
		rayHit.t /= length;
		//p1�������̏ꍇ
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
		//���̊O���̏ꍇ
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
	float tmin = 0.0f;          // -FLT_MAX�ɐݒ肵�Ē����ɂ�����ŏ��̌����𓾂�
	float tmax = FLT_MAX; // (�����ɑ΂���)�������ړ����邱�Ƃ̂ł���ő�̋����ɐݒ�
	
	float p[3];
	p[0] = ray.m_position.x;
	p[1] = ray.m_position.y;
	p[2] = ray.m_position.z;

	float d[3];
	d[0] = ray.m_direction.x;
	d[1] = ray.m_direction.y;
	d[2] = ray.m_direction.z;
	MyVector3 boxSize = GetSize();
	//�l�p�̖ʂ̍Œ�l
	float min[3];
	min[0] = m_center.x - boxSize.x / 2.0f;
	min[1] = m_center.y - boxSize.y / 2.0f;
	min[2] = m_center.z - boxSize.z / 2.0f;

	//�l�p�̖ʂ̍ő�l
	float max[3];
	max[0] = m_center.x + boxSize.x / 2.0f;
	max[1] = m_center.y + boxSize.y / 2.0f;
	max[2] = m_center.z + boxSize.z / 2.0f;

	//EPSILON �����Ȍ덷�@���e�͈�
	// 3�̂��ׂăX���u�ɑ΂���
	for (int i = 0; i < 3; i++) {
		if (std::abs(d[i]) < FLT_EPSILON)
		{
			// �����̓X���u�ɑ΂��ĕ��s�B���_���X���u�̒��ɂȂ���Ό����Ȃ�
			if (p[i] < min[i] || p[i] > max[i]) return hit;
		}
		else
		{
			// �X���u�̋߂����ʂ���щ������ʂƌ������������t�̒l���v�Z
			float ood = 1.0f / d[i];
			float t1 = (min[i] - p[i]) * ood;
			float t2 = (max[i] - p[i]) * ood;
			// t1���߂����ʂƂ̌����At2���������ʂƂ̌����ƂȂ�
			if (t1 > t2) std::swap(t1, t2);
			// �X���u�̌������Ă���Ԋu�Ƃ̌������v�Z
			if (t1 > tmin) tmin = t1;
			if (t2 < tmax) tmax = t2;
			// �X���u�Ɍ������Ȃ����Ƃ�������ΏՓ˂͂Ȃ��̂ł����ɏI��
			if (tmin > tmax)
			{
				return hit;
			}
		}
	}
	//if (!isHit) return false;

	hit.isHit = true;
	// ������3�̃X���u���ׂĂɌ������Ă���B�_(q)�ƌ�����t�̒l(tmin)��Ԃ�
	hit.hitPosition = ray.m_position + ray.m_direction * tmin;
	hit.t = tmin;
	return hit;
}

HitInfo BoundingBox3D::IsCollideRotate(const Line3D & line) const
{
	HitInfo hit;
	MyMatrix4 inv = MyMatrix4::InverseMatrix(m_rotate);
	//box�̈ʒu��0�ł���]���Ă��Ȃ��ꍇ�̃��[�J���ʒu�̐������쐬
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
	//�O�̈ʒu��left�ǂ��O�̏ꍇ
	if (leftUpFront.x >= prevPos.x)
	{
		result.x = -1;
	}
	else if(rightBottomBack.x <= prevPos.x)//�E���O
	{
		result.x = 1;
	}
	//Y
	if (leftUpFront.y >= prevPos.y)
	{
		result.y = -1;
	}
	else if (rightBottomBack.y <= prevPos.y)//�E���O
	{
		result.y = 1;
	}
	//Z
	if (leftUpFront.z >= prevPos.z)
	{
		result.z = -1;
	}
	else if (rightBottomBack.z <= prevPos.z)//�E���O
	{
		result.z = 1;
	}
	return result.Normalize();
}
