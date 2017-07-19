#ifndef		  _MY_VECTOR3_H_
#define		  _MY_VECTOR3_H_

///<summary>Vector3�N���X	��������Ȃ�������������A��������</summary>
class MyVector3
{
public:

	///<summary>�R���X�g���N�^</summary>
	///<param name='x'>X����</param>
	///<param name='y'>Y����</param>
	///<param name='z'>Z����</param>
	MyVector3(float x = 0.0f, float y = 0.0f, float z = 0.0f);
	
	///<summary>���ς̌v�Z</summary>
	///<param name='vec'>�����ƌv�Z����vector</param>
	///<returns>����</returns>
	float Dot(const MyVector3& vec);

	///<summary>���ς��v�Z����</summary>
	///<param name='v1'>���ς��v�Z����vector</param>
	///<param name='v2'>���ς��v�Z����vector</param>
	///<returns>����</returns>
	static float Dot(const MyVector3& v1, const MyVector3& v2);

	///<summary>�O�ς��v�Z����</summary>
	///<param name='vec'>�����ƌv�Z����vector</param>
	///<returns>�O��</returns>
	MyVector3 Cross(const MyVector3& vec);
	///<summary>�O�ς��v�Z����</summary>
	///<param name='v1'>�O�ς��v�Z����vector</param>
	///<param name='v2'>�O�ς��v�Z����vector</param>
	///<returns>�O��</returns>
	static MyVector3 Cross(const MyVector3& v1, const MyVector3& v2);


	///<summary>2�_�Ԃ̋������v�Z����</summary>
	///<param name='v1'>�_�̈ʒu</param>
	///<param name='v2'>�_�̈ʒu</param>
	///<returns>����</returns>
	static float Distance(const MyVector3& v1, const MyVector3& v2);

	///<summary>�x�N�g���̒������v�Z����</summary>
	///<returns>����</returns>
	float Length() const;

	///<summary>�x�N�g���̒������v�Z����</summary>
	///<param name='vec'>�������v�Z����x�N�g��</param>
	///<returns>����</returns>
	static float Length(const MyVector3& vec);

	///<summary>2�x�N�g���̊p�x�����v�Z����</summary>
	///<param name='vec'>�����ƌv�Z����x�N�g��</param>
	///<returns>�p�x�i0�`180�x��rad�@�j</returns>
	float Angle(const MyVector3& vec);

	///<summary>2�x�N�g���̊p�x�����v�Z����</summary>
	///<param name='v1'>�p�x�����v�Z����x�N�g��</param>
	///<param name='v2'>�p�x�����v�Z����x�N�g��</param>
	///<returns>�p�x�i0�`180�x��rad�@�j</returns>
	static float Angle(const MyVector3& v1, const MyVector3& v2);

	///<summary>�x�N�g���̐��K��</summary>
	///<returns>���K�����ꂽ�x�N�g��</returns>
	MyVector3 Normalize();

	///<summary>�x�N�g���̐��K��</summary>
	///<param name='vec'>���K������x�N�g��</param>
	///<returns>���K�����ꂽ�x�N�g��</returns>
	static MyVector3 Normalize(const MyVector3& vec);

	///<summary>�[���x�N�g����Ԃ�</summary>
	///<returns>�[���x�N�g��</returns>
	static MyVector3 Zero();

	///<summary>�x�N�g���̐��ԕ␳</summary>
	///<param name='begin'>�X�^�[�g�ʒu</param>
	///<param name='end'>�I���ʒu</param>
	///<param name='rate'>����(0.0�`1.0)</param>
	static MyVector3 Lerp(const MyVector3& begin, const MyVector3& end, float rate);

public:
	float x;
	float y;
	float z;
};

// �P�����Z�q�I�[�o�[���[�h
MyVector3 operator - (const MyVector3& v);

// ������Z�q�I�[�o�[���[�h
MyVector3& operator +=(MyVector3& v1, const MyVector3& v2);

MyVector3& operator -= (MyVector3& v1, const MyVector3& v2);
MyVector3& operator *= (MyVector3& v, float s);
MyVector3& operator /= (MyVector3& v, float s);
// �Q�����Z�q�I�[�o�[���[�h
MyVector3 operator + (const MyVector3& v1, const MyVector3& v2);
MyVector3 operator - (const MyVector3& v1, const MyVector3& v2);
MyVector3 operator * (const MyVector3& v, float s);
MyVector3 operator * (float s, const MyVector3& v);
MyVector3 operator / (const MyVector3& v, float s);

#endif