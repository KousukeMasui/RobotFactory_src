#include"../Vector/MyVector2.h"

#include"../Shapes\Shapes.h"

class Collision2D
{
public:
	/// <summary>
	/// ���Ɖ~�̓����蔻��
	/// </summary>
	/// <param name="circlePos">�~�̈ʒu�@�d�Ȃ�Ȃ��悤�ɏC�������</param>
	/// <param name="circleRadius">�~�̔��a</param>
	/// <param name="linePos1">�����̎n�_</param>
	/// <param name="linePos2">�����̏I�_</param>
	/// <returns></returns>
	static bool Circle_Line(const MyVector2& circlePos, float circleRadius,
		const MyVector2& linePos1, const MyVector2& linePos2, MyVector2& ansCirclePos);

	/// <summary>
	/// ���Ɛ��̓����蔻��
	/// </summary>
	/// <param name="p0">����1�̎n�_</param>
	/// <param name="p1">����1�̏I�_</param>
	/// <param name="p2">����2�̎n�_</param>
	/// <param name="p3">����2�̏I�_</param>
	/// <param name="I">�������W��Ԃ�</param>
	/// <returns></returns>
	static bool Line_Line(const MyVector2& p0, const MyVector2& p1, const MyVector2& p2, const MyVector2& p3, MyVector2& I);

	static bool Line_Line(const Line2D& l1, const Line2D& l2, MyVector2& I);
	/// <summary>
	/// �J�v�Z���^�Ɖ~�̓����蔻��
	/// </summary>
	/// <param name="p1">�J�v�Z���̐����̎n�_</param>
	/// <param name="p2">�J�v�Z���̐����̏I�_</param>
	/// <param name="cp">�~�̈ʒu</param>
	/// <param name="r">�J�v�Z���̔��a</param>
	/// <param name="cr">�~�̔��a</param>
	/// <returns></returns>
	static bool Capsule_Circle(const MyVector2& p1, const MyVector2& p2, float r, const MyVector2& cp, float cr);

	/// <summary>
	/// ���ƃJ�v�Z���̓����蔻��
	/// </summary>
	/// <param name="p1"></param>
	/// <param name="p2"></param>
	/// <param name="r"></param>
	/// <param name="lp1"></param>
	/// <param name="lp2"></param>
	/// <returns></returns>
	static bool Capsule_Line(const MyVector2& p1, const MyVector2& p2, float r, const MyVector2& lp1, const MyVector2& lp2, MyVector2& contactPos);

	static bool Capsule_Capsule(const MyVector2& p1, const MyVector2& p2, const MyVector2& p3, const MyVector2& p4, float r1, float r2);

	static bool Circle_Ray(const MyVector2& p1, const MyVector2& p2, const MyVector2& pc, float r);


	static bool Square_Point(const MyVector2& point, const MyVector2& squareLeftUp, const MyVector2& squareRightBottom);
};