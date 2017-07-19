#include "Collision2D.h"

/// <summary>
/// ���Ɖ~�̓����蔻��
/// </summary>
/// <param name="circlePos">�~�̈ʒu�@�d�Ȃ�Ȃ��悤�ɏC�������</param>
/// <param name="circleRadius">�~�̔��a</param>
/// <param name="linePos1">�����̎n�_</param>
/// <param name="linePos2">�����̏I�_</param>
/// <returns></returns>

bool Collision2D::Circle_Line(MyVector2 circlePos, float circleRadius, MyVector2 linePos1, MyVector2 linePos2, MyVector2 & ansCirclePos)
{
	MyVector2 v1 = circlePos - linePos1;//p1����̉~�܂ł̃x�N�g��
	MyVector2 v = linePos2 - linePos1;//���̃x�N�g��

	float t = MyVector2::Dot(v1, v) / MyVector2::Dot(v, v);

	MyVector2 vt = v * t;
	MyVector2 vn = v1 - vt;

	//p1�̊O����
	if (t<0)
	{
		//p1�Ɖ~�̓����蔻��
		if (v1.Length() <= circleRadius)
		{
			ansCirclePos = linePos1 + (circleRadius * MyVector2::Normalize(vn));
			return true;
		}
	}
	else//p1�̓���
	{
		if (t>1)//p2�̊O��
		{
			//p2�̊O���ɂ���ꍇ�̏���
			MyVector2 v2 = circlePos - linePos2;
			if (t > 1 && v2.Length() <= circleRadius)
			{
				ansCirclePos = linePos2 + (circleRadius * MyVector2::Normalize(vn));
				return true;
			}
		}
		else//p1��p2�̊Ԃ̏���
		{
			//p1�̊O���ɂ���ꍇ�̏���

			//p1p2�̊Ԃ̏���
			if ((t > 0 && t < 1) && vn.Length() <= circleRadius)
			{
				ansCirclePos = linePos1 + vt + (circleRadius * MyVector2::Normalize(vn));
				return true;
			}
		}
	}
	return false;
}

/// <summary>
/// ���Ɛ��̓����蔻��
/// </summary>
/// <param name="p0">����1�̎n�_</param>
/// <param name="p1">����1�̏I�_</param>
/// <param name="p2">����2�̎n�_</param>
/// <param name="p3">����2�̏I�_</param>
/// <param name="I">�������W��Ԃ�</param>
/// <returns></returns>

bool Collision2D::Line_Line(MyVector2 p0, MyVector2 p1, MyVector2 p2, MyVector2 p3, MyVector2 & I)
{
	MyVector2 a = p1 - p0;//����1
	MyVector2 b = p3 - p2;//����2

	MyVector2 c = p2 - p0;

	float t1 = (MyVector2::Cross(c, a) / MyVector2::Cross(a, b));
	if (0 > t1 || 1<t1) return false;

	float t2 = (MyVector2::Cross(c, b) / MyVector2::Cross(a, b));
	if (0 > t2 || 1<t2) return false;

	//�������W�����߂�
	I = p0 + (t2 * a);
	return true;
}

bool Collision2D::Line_Line(Line2D l1, Line2D l2, MyVector2 & I)
{
	return Line_Line(l1.p1, l1.p2, l2.p1, l2.p2, I);
}

/// <summary>
/// �J�v�Z���^�Ɖ~�̓����蔻��
/// </summary>
/// <param name="p1">�J�v�Z���̐����̎n�_</param>
/// <param name="p2">�J�v�Z���̐����̏I�_</param>
/// <param name="cp">�~�̈ʒu</param>
/// <param name="r">�J�v�Z���̔��a</param>
/// <param name="cr">�~�̔��a</param>
/// <returns></returns>

bool Collision2D::Capsule_Circle(MyVector2 p1, MyVector2 p2, float r, MyVector2 cp, float cr)
{
	MyVector2 v = MyVector2();
	return Circle_Line(cp, cr + r, p1, p2, v);
}

/// <summary>
/// ���ƃJ�v�Z���̓����蔻��
/// </summary>
/// <param name="p1"></param>
/// <param name="p2"></param>
/// <param name="r"></param>
/// <param name="lp1"></param>
/// <param name="lp2"></param>
/// <returns></returns>

bool Collision2D::Capsule_Line(MyVector2 p1, MyVector2 p2, float r, MyVector2 lp1, MyVector2 lp2, MyVector2 contactPos)
{
	if (Line_Line(p1, p2, lp1, lp2, contactPos)) return true;
	if (Circle_Line(p1, r, lp1, lp2, contactPos)) return true;
	if (Circle_Line(p2, r, lp1, lp2, contactPos)) return true;

	return false;
}

bool Collision2D::Capsule_Capsule(MyVector2 p1, MyVector2 p2, MyVector2 p3, MyVector2 p4, float r1, float r2)
{

	float radius = r1 + r2;

	return Capsule_Line(p1, p2, radius, p3, p4, MyVector2());
}

bool Collision2D::Circle_Ray(MyVector2 p1, MyVector2 p2, MyVector2 pc, float r)
{
	MyVector2 v = p2 - p1;//ray�̕���
	MyVector2 v1 = p1 - pc;//�~����ray�̎n�_�ւ̃x�N�g��
	float b = MyVector2::Dot(v, v1);
	float c = b - r * r;
	float d = b * b - c;
	if (d >= 0)
	{
		//float t = -b - (float)Math.Sqrt(d);
		return true;
	}

	return false;
}

bool Collision2D::Square_Point(MyVector2 point, MyVector2 squareLeftUp, MyVector2 squareRightBottom)
{
	if (point.x > squareRightBottom.x || point.x < squareLeftUp.x) return false;
	if (point.y > squareRightBottom.y || point.y < squareLeftUp.y) return false;
	return true;
}
