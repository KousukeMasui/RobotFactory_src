#ifndef _MY_MATRIX4_H_
#define _MY_MATRIX4_H_

#include<math.h>
class MyVector3;
class MyQuaternion;
class Converter;
class MyMatrix4
{

public:
	MyMatrix4(
		float m00, float m01, float m02, float m03,
		float m10, float m11, float m12, float m13,
		float m20, float m21, float m22, float m23,
		float m30, float m31, float m32, float m33);

	MyMatrix4();
	static MyMatrix4 Identity();

	static MyMatrix4 Scale(float x, float y, float z);

	static MyMatrix4 Scale(const MyVector3& scale);

	static MyMatrix4 Rotate(const MyQuaternion& q);

	static MyMatrix4 Rotate(const MyVector3& axis, float degree);
	//回転行列の作成
	static MyMatrix4 RotateX(float rad);
	static MyMatrix4 RotateY(float rad);
	static MyMatrix4 RotateZ(float rad);



	static MyMatrix4 SetForward(const MyVector3& forward, const MyVector3& top);
	static MyMatrix4 SetForwardAndLeft(const MyVector3& forward, const MyVector3& left);
	MyMatrix4 SetPosition(const MyVector3& pos);


	MyMatrix4 Multiply(const MyMatrix4& mat);

	static MyMatrix4 Translate(const MyVector3& pos);

	static MyMatrix4 Translate(float x, float y, float z);

	MyVector3 GetLeft() const;
	MyVector3 GetTop() const;
	MyVector3 GetForward() const;
	MyVector3 GetPosition() const;

	MyVector3 GetScale() const;
	MyQuaternion GetRotation() const;
	MyMatrix4 GetRotationMatrix() const;

	/// <summary>
	/// ビューマトリックス
	/// </summary>
	/// <param name="cameraPosition">カメラの位置</param>
	/// <param name="targetPosition">注視点</param>
	/// <param name="CameraUpVector">カメラの上方向</param>
	/// <returns></returns>
	static MyMatrix4 CreateLookAt(
		const MyVector3& cameraPosition,
		const MyVector3& targetPosition,
		const MyVector3& CameraUpVector);

	
	//透視変換行列を作成する関数
	static MyMatrix4 Perspective(float fov, float aspect, float zn, float zf);

	//スクリーン座標変換行列を作成する関数
	MyMatrix4 screen(float x, float y, float width, float height);

	static MyMatrix4 Multiply(MyMatrix4& m1, const MyMatrix4& m2);

	static MyMatrix4 YawPitchRoll(float yaw, float pitch, float roll);

	static MyMatrix4 CreateWorld(const MyVector3& scale, const MyQuaternion& rotation, const MyVector3& translate);
	static MyMatrix4 CreateWorld(const MyVector3& scale, const MyMatrix4& rotation, const MyVector3& translation);
	static MyMatrix4 CreateWorld(const MyVector3& position, const MyVector3& forward, const MyVector3& up);
	static MyMatrix4 InverseMatrix(const MyMatrix4& mat);
	//転置行列
	static MyMatrix4 Transpose(const MyMatrix4& mat);

	static MyMatrix4 Lerp(const MyMatrix4& value1, const MyMatrix4& value2, float amount);
	void Decompose(MyVector3& scale, MyQuaternion& rotation, MyVector3& translation);
	static MyMatrix4 NormalizeRotationMatrix(const MyMatrix4& mat);
	MyMatrix4& NormalizeRotationMatrix();

	static MyMatrix4 CreateFromAxisAngle(const MyVector3& axis, float degree);

	//逆行列(回転と平行移動のみ)
	static MyMatrix4 InverseFast(const MyMatrix4& mat);
	//スクリーン座標に変換する行列を作る
	static MyMatrix4 CreateScreen(float x, float y, float width, float height);
	static MyVector3 GetRad(const MyMatrix4& mat);
	static MyVector3 GetDegree(const MyMatrix4& mat);

	static MyMatrix4 RotateZXY(const MyVector3& rad);
private:
	//これらは回転しないので問題が起きる可能性があるのでprivate
	
	MyMatrix4 SetForward(const MyVector3& forward);
	MyMatrix4 SetTop(const MyVector3& top);
	MyMatrix4 SetLeft(const MyVector3& left);

public:
	float m[4][4];
};

MyMatrix4 operator *(const MyMatrix4& m1, const MyMatrix4& m2);

MyMatrix4& operator *=(MyMatrix4& m1, const MyMatrix4& m2);
MyVector3 operator *=(MyVector3& vec,const MyMatrix4& mat);

MyVector3 operator *(const MyMatrix4& mat, const MyVector3& vec);

MyVector3 operator * (const MyVector3& vec,const MyMatrix4& mat);

#endif