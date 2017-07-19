#ifndef	_Shape3D_H_
#define	_Shape3D_H_

#include"Math/Vector/MyVector3.h"
#include<vector>
#include"Math/Matrix/MyMatrix4.h"
//�}�`�̐e�N���X�@�q�Ŏg���ϐ���S�Ċi�[���āA�����蔻����ȒP�ɏo����悤�ɂ���
class Shape3D
{
public:
	Shape3D();

	//�|���S���p
	explicit Shape3D(const std::vector<MyVector3>& v);
	Shape3D(const MyVector3& p, const std::vector<MyVector3>& v);
	
	Shape3D(const MyVector3& p1, const MyVector3& p2, float radius);
	Shape3D(const MyVector3& p, float radius);


	//�ʒu�̐ݒ� vertices�͌��ݓ������Ă��Ȃ�
	virtual void Translate(const MyVector3& vec);
public:
	//�ʒu����1	1�������W�������Ȃ��}�`�͂����ɍ��W���i�[
	MyVector3 p1;
	//�ʒu����2 ����J�v�Z���Ɏg�p
	MyVector3 p2;
	//���a
	float radius;

	//�傫��
	MyVector3 size;

	//��]�s��
	MyMatrix4 rotate;

	//�|���S���p
	std::vector<MyVector3> vertices;
};

#endif