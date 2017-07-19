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
enum class VertexIndices//���_�̗�
{
	MIN = 0,
	MIN_MIN_MAX,
	MIN_MAX_MIN,
	MIN_MAX_MAX,
	MAX_MIN_MIN,
	MAX_MIN_MAX,
	MAX_MAX_MIN,
	MAX,

	COUNT = 8//���v��
};
struct BoundingBox3D
{
	BoundingBox3D(const MyVector3& min, const MyVector3& max,const MyVector3& center);
	BoundingBox3D(const MyVector3& center, const MyVector3& size, const MyMatrix4& rotate);
	~BoundingBox3D();
	void Rotate(const MyMatrix4& rotate);

	//���_���W���擾
	MyVector3 GetVertexPosition(VertexIndices vertex) const;
	std::vector<MyVector3> GetVertexPositions() const;
	//��]�Ȃ��̒��_���W
	MyVector3 GetNonRotateVertexPosition(VertexIndices vertex) const;
	std::vector<MyVector3> GetNonRotateVertexPositions(VertexIndices vertex) const;
	//�T�C�Y���擾
	MyVector3 GetSize() const;

	bool IsInside(const MyVector3& position) const;
	//�����蔻��
	HitInfo IsCollide(const Sphere& sphere) const;
	HitInfo IsCollide(const Capsule& capsule) const;
	HitInfo IsCollide(const Line3D& line) const;
	HitInfo IsCollide(const Ray& ray) const;
	HitInfo IsCollideRotate(const Line3D& line) const;
	HitInfo IsCollideRotate(const Capsule& Capsule) const;
	HitInfo IsCollideRotate(const Ray& ray) const;

	//�ǂ̖ʂ̕������𒲂ׂĂ��̖@����Ԃ�
	MyVector3 CalcNormal(const MyVector3& contactPos,const MyVector3& prevPos) const;
	//���S���W
	MyVector3 m_center;
	//���_���W
	std::vector<MyVector3> m_vertices;
	//��]�s��
	MyMatrix4 m_rotate;
};

#endif