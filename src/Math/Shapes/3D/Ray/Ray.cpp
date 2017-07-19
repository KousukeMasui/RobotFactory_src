#include "Ray.h"
Ray::Ray(const MyVector3& p, const MyVector3& direction):
	m_position(p),
	m_direction(MyVector3::Normalize(direction))
{

}


// 2D���W���烌�C���v�Z����

Ray Ray::CalculateRay(const MyVector2 & position, const MyMatrix4 & screen, const MyMatrix4 & projection, const MyMatrix4 & view)
{
	MyMatrix4 un_project = MyMatrix4::InverseMatrix(view * projection * screen);
	// �X�N���[�����W����߃N���b�v�ʂ̃��[���h���W�ɕϊ�
	MyVector3 n = MyVector3(position.x, position.y, -1.0f)*un_project;
	// �X�N���[�����W���牓�N���b�v�ʂ̃��[���h���W�ɕϊ�
	MyVector3 f = MyVector3(position.x, position.y, 1.0f)*un_project;
	// �߃N���b�v�ʂ��牓�N���b�v�ʂɌ��������C���쐬
	return Ray(n, (f - n).Normalize());
}

Ray::~Ray()
{
}

Ray Ray::Transform(const MyMatrix4 & matrix)
{
	return Ray(m_position * matrix,m_direction * matrix.GetRotationMatrix());
}
