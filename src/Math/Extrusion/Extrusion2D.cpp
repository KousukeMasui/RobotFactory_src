#include "Extrusion2D.h"
#include"Math\Collision\Collision2D.h"

MyVector2 Extrusion2D::Box_ExtrusionSphere(MyVector2 SpherePos, float radius, MyVector2 boxPos, std::vector<MyVector2> vertices, MyVector2 contactPos)
{
	//�l�p�̒��S����]���ɂ������̍��W
	MyVector2 otherPos = SpherePos - boxPos;
	
	MyVector2 vec = MyVector2();
	//�l�p�̊O�̏ꍇ����ɓ����v���O����
	MyVector2 direction = otherPos-(contactPos - boxPos);//2�_�Ԃ̋���
	float length = direction.Length();
	float directionLength = radius - length;//�߂肱�񂾒���

	//�l�p�̒��ɂ�����
	if (length <= 0.01f)//Normalize�h�~
	{
		//direction = otherPos;
		for (int i = 0; i < vertices.size(); i++)
		{
			MyVector2 p1 = vertices[i];
			int v = (i + 1) % vertices.size();
			MyVector2 p2 = vertices[(i + 1) % vertices.size()];

			MyVector2 lineContactPos;
			if (Collision2D::Line_Line(boxPos, boxPos + (otherPos*100.0f), p1, p2, lineContactPos))
			{
  				direction = lineContactPos - boxPos;
				length = direction.Length();
				break;
			}
		}
		direction.Normalize();//���K��

		direction *= (length+radius);//�߂肱�񂾒����̃x�N�g����
		MyVector2 p = boxPos + direction;
		return p;
	}
	direction.Normalize();//���K��

	direction *= directionLength;//�߂肱�񂾒����̃x�N�g����

	MyVector2 p = otherPos + direction;

	p += boxPos;

	return p;
}
