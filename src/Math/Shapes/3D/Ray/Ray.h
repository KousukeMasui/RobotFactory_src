#ifndef	_RAY_H_
#define	_RAY_H_

#include"Math/Vector/MyVector3.h"
#include"Math/Vector/MyVector2.h"
#include"Math/Matrix/MyMatrix4.h"

struct Ray
{
	Ray(const MyVector3& position, const MyVector3& direction);


	// 2D���W���烌�C���v�Z����
	static Ray CalculateRay(
		const MyVector2& position,	// �X�N���[�����W
		const MyMatrix4& screen,		// �X�N���[���ϊ��s��
		const MyMatrix4& projection,	// �����ϊ��s��
		const MyMatrix4& view			// ����ϊ��s��
		);
	~Ray();

	Ray Transform(const MyMatrix4& matrix);

	MyVector3 m_position;
	//����
	MyVector3 m_direction;
};

#endif