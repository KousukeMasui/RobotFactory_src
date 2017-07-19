#ifndef	_LINE_3D_H_
#define	_LINE_3D_H_

#include"Math/Vector/MyVector3.h"
#include"Math/Matrix/MyMatrix4.h"
#include"../Shape3D.h"
struct Line3D : public Shape3D
{
	Line3D(const MyVector3& start, const MyVector3& end);
	//������Ԃ�
	float Length() const;
	//�n�_����I�_�ւ̕�����Ԃ�
	MyVector3 Direction() const;
	//�_�܂ł̍ŒZ���������߂�
	float PointLength(const MyVector3& point) const;

	//���W�ϊ�
	Line3D Transform(const MyMatrix4& matrix);

	void Translate(const MyVector3& position) override;

	MyVector3 m_start;
	MyVector3 m_end;
};

#endif