#include"MyMatrix4.h"


#include"../Vector/MyVector3.h"
#include"MyQuaternion.h"
#include"../Converter.h"
#include<cmath>
#include"Math/MyMath.h"

MyMatrix4::MyMatrix4(
	float m00, float m01, float m02, float m03,
	float m10, float m11, float m12, float m13,
	float m20, float m21, float m22, float m23,
	float m30, float m31, float m32, float m33)
{
	m[0][0] = m00; m[0][1] = m01; m[0][2] = m02; m[0][3] = m03;
	m[1][0] = m10; m[1][1] = m11; m[1][2] = m12; m[1][3] = m13;
	m[2][0] = m20; m[2][1] = m21; m[2][2] = m22; m[2][3] = m23;
	m[3][0] = m30; m[3][1] = m31; m[3][2] = m32; m[3][3] = m33;
}

MyMatrix4::MyMatrix4()
{
	for (int i = 0; i < 4; i++)
	{
		for (int j = 0; j < 4; j++)
		{
			m[i][j] = 0;
		}
	}
}

MyMatrix4 MyMatrix4::Identity()
{
	MyMatrix4 result;
	for (int i = 0; i < 4; i++)
	{
		for (int j = 0; j< 4; j++)
		{
			if (i == j) result.m[i][j] = 1;
			else result.m[i][j] = 0;
		}
	}

	return result;
}

MyMatrix4 MyMatrix4::Scale(float x, float y, float z)
{
	return MyMatrix4(
		x, 0.0f, 0.0f, 0.0f,
		0.0f, y, 0.0f, 0.0f,
		0.0f, 0.0f, z, 0.0f,
		0.0f, 0.0f, 0.0f, 1.0f);
}

MyMatrix4 MyMatrix4::Scale(const MyVector3& scale)
{
	return Scale(scale.x, scale.y, scale.z);
}

MyMatrix4 MyMatrix4::Rotate(const MyQuaternion & q)
{
	float xx = q.x * q.x * 2.0f;
	float yy = q.y * q.y * 2.0f;
	float zz = q.z * q.z * 2.0f;
	float xy = q.x * q.y * 2.0f;
	float xz = q.x * q.z * 2.0f;
	float yz = q.y * q.z * 2.0f;
	float wx = q.w * q.x * 2.0f;
	float wy = q.w * q.y * 2.0f;
	float wz = q.w * q.z * 2.0f;

	return MyMatrix4(
		1.0f - yy - zz, xy + wz, xz - wy, 0.0f,
		xy - wz, 1.0f - xx - zz, yz + wx, 0.0f,
		xz + wy, yz - wx, 1.0f - xx - yy, 0.0f,
		0.0f, 0.0f, 0.0f, 1.0f);
}

MyMatrix4 MyMatrix4::Rotate(const MyVector3 & axis, float degree)
{
	return Rotate(MyQuaternion(axis, degree));
}
MyMatrix4 MyMatrix4::RotateX(float rad)
{
	float cos = cosf(rad);
	float sin = sinf(rad);

	return MyMatrix4(
		1, 0, 0, 0,
		0, cos, sin, 0,
		0, -sin, cos, 0,
		0, 0, 0, 1);
}

MyMatrix4 MyMatrix4::RotateY(float rad)
{
	float cos = cosf(rad);
	float sin = sinf(rad);

	return MyMatrix4(
		cos, 0, -sin, 0,
		0, 1, 0, 0,
		sin, 0, cos, 0,
		0, 0, 0, 1);
}

MyMatrix4 MyMatrix4::RotateZ(float rad)
{
	float cos = cosf(rad);
	float sin = sinf(rad);

	return MyMatrix4(
		cos, sin, 0, 0,
		-sin, cos, 0, 0,
		0, 0, 1, 0,
		0, 0, 0, 1);
}

MyMatrix4 MyMatrix4::SetForward(const MyVector3& forward, const MyVector3& top)
{
	MyVector3 f = MyVector3::Normalize(forward);
	MyVector3 left = MyVector3::Normalize(MyVector3::Cross(top, f));

	MyMatrix4 result = MyMatrix4::Identity();
	return result.SetForward(f).SetLeft(left).SetTop(top);
}

MyMatrix4 MyMatrix4::SetForwardAndLeft(const MyVector3& forward, const MyVector3& left)
{
	MyVector3 top = MyVector3::Cross(left, forward);

	MyMatrix4 result = MyMatrix4::Identity();
	return result.SetForward(forward).SetLeft(left).SetTop(top);
}

MyMatrix4 MyMatrix4::SetPosition(const MyVector3& pos)
{
	m[3][0] = pos.x;
	m[3][1] = pos.y;
	m[3][2] = pos.z;
	return *this;
}

MyMatrix4 MyMatrix4::SetForward(const MyVector3& forward)
{
	m[2][0] = forward.x;
	m[2][1] = forward.y;
	m[2][2] = forward.z;
	return *this;
}

MyMatrix4 MyMatrix4::SetTop(const MyVector3& top)
{
	m[1][0] = top.x;
	m[1][1] = top.y;
	m[1][2] = top.z;

	return *this;
}

MyMatrix4 MyMatrix4::SetLeft(const MyVector3& left)
{
	m[0][0] = left.x;
	m[0][1] = left.y;
	m[0][2] = left.z;

	return *this;
}

MyMatrix4 MyMatrix4::Multiply(const MyMatrix4& mat)
{
	MyMatrix4 my = MyMatrix4();
	for (int i = 0; i < 4; i++)
	{
		for (int j = 0; j < 4; j++)
		{
			for (int k = 0; k < 4; k++)
			{
				my.m[i][j] += m[i][k] * mat.m[k][j];
			}
		}
	}
	return my;
}

MyMatrix4 MyMatrix4::Translate(const MyVector3& pos)
{
	return Translate(pos.x, pos.y, pos.z);
}

MyMatrix4 MyMatrix4::Translate(float x, float y, float z)
{
	MyMatrix4 mat = MyMatrix4::Identity();

	mat.m[3][0] = x;
	mat.m[3][1] = y;
	mat.m[3][2] = z;

	return mat;
}

MyVector3 MyMatrix4::GetLeft() const
{
	return MyVector3(m[0][0], m[0][1], m[0][2]);
}

MyVector3 MyMatrix4::GetTop() const
{
	return MyVector3(m[1][0], m[1][1], m[1][2]);
}

MyVector3 MyMatrix4::GetForward() const
{
	return MyVector3(m[2][0], m[2][1], m[2][2]);
}

MyVector3 MyMatrix4::GetPosition() const
{
	return MyVector3(m[3][0], m[3][1], m[3][2]);
}

MyVector3 MyMatrix4::GetScale() const
{
	return MyVector3(GetLeft().Length(),GetTop().Length(),GetForward().Length());
}

MyQuaternion MyMatrix4::GetRotation() const
{
	return MyQuaternion::CreateQuaternion(NormalizeRotationMatrix(*this));
}

MyMatrix4 MyMatrix4::GetRotationMatrix() const
{
	return MyMatrix4(*this).SetPosition(MyVector3::Zero());
}

MyMatrix4 MyMatrix4::CreateLookAt(
	const MyVector3& cameraPosition,
	const MyVector3& targetPosition,
	const MyVector3& CameraUpVector)
{
	MyVector3 z = MyVector3::Normalize(cameraPosition - targetPosition);
	MyVector3 x = MyVector3::Normalize(MyVector3::Cross(CameraUpVector, z));
	MyVector3 y = MyVector3::Cross(z, x);
	//ÉrÉÖÅ[ïœä∑çsóÒ
	MyMatrix4 view = MyMatrix4(
		x.x, y.x, z.x, 0.0f,
		x.y, y.y, z.y, 0.0f,
		x.z, y.z, z.z, 0.0f,
		-MyVector3::Dot(cameraPosition,x), -MyVector3::Dot(cameraPosition, y), -MyVector3::Dot(cameraPosition, z), 1.0f);

	return view;
}

MyMatrix4 MyMatrix4::Perspective(float fov, float aspect, float zn, float zf)
{
	float ys = 1.0f / tanf(Converter::DegToRad(fov / 2.0f));
	float xs = ys / aspect;
	MyMatrix4 result = {
		xs, 0.0f, 0.0f, 0.0f,
		0.0f, ys, 0.0f, 0.0f,
		0.0f, 0.0f, (zf + zn) / (zn - zf), -1.0f,
		0.0f, 0.0f, (2.0f*zf*zn) / (zn - zf), 0.0f
	};
	return result;
}

MyMatrix4 MyMatrix4::screen(float x, float y, float width, float height)
{
	float w = width / 2.0f;
	float h = height / 2.0f;
	MyMatrix4 result = {
		w, 0.0f, 0.0f, 0.0f,
		0.0f, -h, 0.0f, 0.0f,
		0.0f, 0.0f, 1.0f, 0.0f,
		w + x, h + y, 0.0f, 1.0f
	};
	return result;
}

MyMatrix4 MyMatrix4::Multiply(MyMatrix4& m1, const MyMatrix4& m2)
{
	return m1.Multiply(m2);
}

MyMatrix4 MyMatrix4::YawPitchRoll(float yaw, float pitch, float roll)
{
	return MyMatrix4::RotateZ(roll)
		*  MyMatrix4::RotateY(pitch)
		*  MyMatrix4::RotateX(yaw);
}

MyMatrix4 MyMatrix4::CreateWorld(const MyVector3 & scale, const MyQuaternion & rotation, const MyVector3 & translate)
{
	return MyMatrix4::Scale(scale) * MyMatrix4::Rotate(rotation) * MyMatrix4::Translate(translate);
}

MyMatrix4 MyMatrix4::CreateWorld(const MyVector3 & scale, const MyMatrix4 & rotation, const MyVector3 & translation)
{
	return Scale(scale) * rotation * Translate(translation);
}

MyMatrix4 MyMatrix4::CreateWorld(const MyVector3 & position, const MyVector3 & forward, const MyVector3 & up)
{
	MyVector3 l = MyVector3::Normalize(MyVector3::Cross(up, forward));
	MyVector3 u = MyVector3::Normalize(MyVector3::Cross(forward, l));
	MyVector3 f = MyVector3::Cross(l, u);
	MyMatrix4 result = MyMatrix4::Identity();
	result.SetForward(f);
	result.SetTop(u);
	result.SetLeft(l);
	result.SetPosition(position);
	return result;
}

MyMatrix4 MyMatrix4::InverseMatrix(const MyMatrix4 & mat)
{
	float a0 = mat.m[0][0] * mat.m[1][1] - mat.m[0][1] * mat.m[1][0];
	float a1 = mat.m[0][0] * mat.m[1][2] - mat.m[0][2] * mat.m[1][0];
	float a2 = mat.m[0][0] * mat.m[1][3] - mat.m[0][3] * mat.m[1][0];
	float a3 = mat.m[0][1] * mat.m[1][2] - mat.m[0][2] * mat.m[1][1];
	float a4 = mat.m[0][1] * mat.m[1][3] - mat.m[0][3] * mat.m[1][1];
	float a5 = mat.m[0][2] * mat.m[1][3] - mat.m[0][3] * mat.m[1][2];
	float b0 = mat.m[2][0] * mat.m[3][1] - mat.m[2][1] * mat.m[3][0];
	float b1 = mat.m[2][0] * mat.m[3][2] - mat.m[2][2] * mat.m[3][0];
	float b2 = mat.m[2][0] * mat.m[3][3] - mat.m[2][3] * mat.m[3][0];
	float b3 = mat.m[2][1] * mat.m[3][2] - mat.m[2][2] * mat.m[3][1];
	float b4 = mat.m[2][1] * mat.m[3][3] - mat.m[2][3] * mat.m[3][1];
	float b5 = mat.m[2][2] * mat.m[3][3] - mat.m[2][3] * mat.m[3][2];
	float det = a0*b5 - a1*b4 + a2*b3 + a3*b2 - a4*b1 + a5*b0; 
	if (det == 0.0f) {
		return mat; // ãtçsóÒÇ™ë∂ç›ÇµÇ»Ç¢ÅI
	}
	float invDet = 1.0f / det;

	return MyMatrix4(
		( mat.m[1][1] * b5 - mat.m[1][2] * b4 + mat.m[1][3] * b3) * invDet,
		(-mat.m[0][1] * b5 + mat.m[0][2] * b4 - mat.m[0][3] * b3) * invDet,
		( mat.m[3][1] * a5 - mat.m[3][2] * a4 + mat.m[3][3] * a3) * invDet,
		(-mat.m[2][1] * a5 + mat.m[2][2] * a4 - mat.m[2][3] * a3) * invDet,
		(-mat.m[1][0] * b5 + mat.m[1][2] * b2 - mat.m[1][3] * b1) * invDet,
		( mat.m[0][0] * b5 - mat.m[0][2] * b2 + mat.m[0][3] * b1) * invDet,
		(-mat.m[3][0] * a5 + mat.m[3][2] * a2 - mat.m[3][3] * a1) * invDet,
		( mat.m[2][0] * a5 - mat.m[2][2] * a2 + mat.m[2][3] * a1) * invDet,
		( mat.m[1][0] * b4 - mat.m[1][1] * b2 + mat.m[1][3] * b0) * invDet,
		(-mat.m[0][0] * b4 + mat.m[0][1] * b2 - mat.m[0][3] * b0) * invDet,
		( mat.m[3][0] * a4 - mat.m[3][1] * a2 + mat.m[3][3] * a0) * invDet,
		(-mat.m[2][0] * a4 + mat.m[2][1] * a2 - mat.m[2][3] * a0) * invDet,
		(-mat.m[1][0] * b3 + mat.m[1][1] * b1 - mat.m[1][2] * b0) * invDet,
		( mat.m[0][0] * b3 - mat.m[0][1] * b1 + mat.m[0][2] * b0) * invDet,
		(-mat.m[3][0] * a3 + mat.m[3][1] * a1 - mat.m[3][2] * a0) * invDet,
		( mat.m[2][0] * a3 - mat.m[2][1] * a1 + mat.m[2][2] * a0) * invDet );
}

MyMatrix4 MyMatrix4::Transpose(const MyMatrix4 & mat)
{
	MyMatrix4 result = MyMatrix4();
	for (int i = 0; i < 4; i++)
	{
		for (int j = 0; j < 4; j++)
		{
			result.m[i][j] = mat.m[j][i];
		}
	}

	return result;
}

MyMatrix4 MyMatrix4::Lerp(const MyMatrix4 & value1, const MyMatrix4 & value2, float amount)
{
	MyVector3 scale = MyVector3::Lerp(value1.GetScale(), value2.GetScale(), amount);
	float dot = value1.GetRotation().Dot(value2.GetRotation());
	//íZÇ¢ï˚Ç…ï‚ä‘
	MyQuaternion rotate;
	if (dot >0.0f)
		rotate = MyQuaternion::Slerp(value1.GetRotation(), value2.GetRotation(), amount);
	else
		rotate = MyQuaternion::Slerp(value1.GetRotation(), -value2.GetRotation(), amount);

	MyVector3 translation = MyVector3::Lerp(value1.GetPosition(), value2.GetPosition(), amount);
	return MyMatrix4::CreateWorld(scale, rotate, translation);
}

void MyMatrix4::Decompose(MyVector3 & scale, MyQuaternion & rotation, MyVector3 & translation)
{
	scale = GetScale();
	rotation = GetRotation();
	translation = GetPosition();
}

MyMatrix4 MyMatrix4::NormalizeRotationMatrix(const MyMatrix4 & mat)
{
	return MyMatrix4(mat).NormalizeRotationMatrix();
}

MyMatrix4 & MyMatrix4::NormalizeRotationMatrix()
{
	MyVector3 l = MyVector3::Normalize(MyVector3::Cross(GetTop(), GetForward()));
	MyVector3 u = MyVector3::Normalize(MyVector3::Cross(GetForward(), l));
	MyVector3 f = MyVector3::Normalize(MyVector3::Cross(l,u));

	MyMatrix4 result = MyMatrix4::Identity();
	result.SetLeft(l);
	result.SetTop(u);
	result.SetForward(f);
	*this = result;
	return *this;
}

MyMatrix4 MyMatrix4::CreateFromAxisAngle(const MyVector3& axis, float degree)
{
	return Rotate(MyQuaternion(axis,degree));
}

MyMatrix4 MyMatrix4::InverseFast(const MyMatrix4 & mat)
{
	//âÒì]çsóÒÇÃãtçsóÒÇçÏê¨
	MyMatrix4 inv_rotation = MyMatrix4::Transpose(mat.GetRotationMatrix());
	//ïΩçsà⁄ìÆê¨ï™ÇÃãtïœä∑
	MyVector3 inv_translation = mat.GetPosition() * inv_rotation;
	//ãtçsóÒÇï‘Ç∑
	return inv_rotation.Translate(inv_translation);
}

MyMatrix4 MyMatrix4::CreateScreen(float x, float y, float width, float height)
{
	float w = width / 2.0f;
	float h = height / 2.0f;

	return MyMatrix4(
		w, 0.0f, 0.0f, 0.0f,
		0.0f, -h, 0.0f, 0.0f,
		0.0f, 0.0f, 1.0f, 0.0f,
		w + x, h + y, 0.0f, 1.0f);
}

MyVector3 MyMatrix4::GetRad(const MyMatrix4 & mat)
{
	MyVector3 result;
	double threshold = 0.001;

	if (abs(mat.m[1][2] - 1.0) < threshold)// R(2,1) = sin(x) = 1ÇÃéû
		result = MyVector3(MyMath::PI / 2, 0, atan2(mat.m[1][0], mat.m[0][0]));
	else if (abs(mat.m[1][2] + 1.0) < threshold)// R(2,1) = sin(x) = -1ÇÃéû
		result = MyVector3(-MyMath::PI / 2,0, atan2(mat.m[1][0], mat.m[0][0]));
	else 
		result = MyVector3(asin(mat.m[1][2]),atan2(-mat.m[2][0], mat.m[2][2]),atan2(-mat.m[0][1], mat.m[1][1]));
	return result;
}

MyVector3 MyMatrix4::GetDegree(const MyMatrix4 & mat)
{
	auto rad = GetRad(mat);
	return MyVector3(Converter::RadToDeg(rad.x), Converter::RadToDeg(rad.y), Converter::RadToDeg(rad.z));
}

MyMatrix4 MyMatrix4::RotateZXY(const MyVector3 & rad)
{
	return MyMatrix4::RotateZ(rad.z) *MyMatrix4::RotateX(rad.x)*MyMatrix4::RotateY(rad.y);
	//float cosX = std::cosf(rad.x);
	//float cosY = std::cosf(rad.y);
	//float cosZ = std::cosf(rad.z);
	//float sinX = std::sinf(rad.x);
	//float sinY = std::sinf(rad.y);
	//float sinZ = std::sinf(rad.z);
	//return MyMatrix4(cosY * cosZ - sinX * sinY * sinZ, -cosX * sinZ, sinY * cosZ + sinX * cosY *sinZ,0,
	//	cosY*sinZ + sinX*sinY*cosZ, cosX*cosZ, sinZ*sinY - sinZ*cosY*cosZ,0,
	//	-cosX*sinY, sinX, cosX*cosY,0,
	//	0,0,0,1);
}

MyMatrix4 operator*(const MyMatrix4& m1, const MyMatrix4& m2)
{
	return MyMatrix4(m1).Multiply(m2);
}

MyMatrix4 & operator*=(MyMatrix4 & m1, const MyMatrix4& m2)
{
	m1 = m1* m2;
	return m1;
}

MyVector3 operator*=(MyVector3& vec, const MyMatrix4& mat)
{
	return vec = vec * mat;
}

MyVector3 operator*(const MyMatrix4& mat, const MyVector3& vec)
{
	MyVector3 result = {
		(vec.x * mat.m[0][0] + vec.y * mat.m[1][0] + vec.z * mat.m[2][0] + mat.m[3][0]),
		(vec.x * mat.m[0][1] + vec.y * mat.m[1][1] + vec.z * mat.m[2][1] + mat.m[3][1]),
		(vec.x * mat.m[0][2] + vec.y * mat.m[1][2] + vec.z * mat.m[2][2] + mat.m[3][2])
	};
	return result;
}

MyVector3 operator*(const MyVector3& vec, const MyMatrix4& mat)
{
	return mat * vec;
}
