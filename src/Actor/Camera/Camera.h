#ifndef	  _CAMERA_H_
#define	  _CAMERA_H_
#include"Object\Object.h"
class Camera:public Object
{
public:
	explicit Camera();
	explicit Camera(const MyVector3& rad);

	virtual void Update(float deltaTime);
	void Draw()const;

	//操作可能かの設定
	void Controll(bool isControll);
private:
	//カメラの移動処理
	void CameraMove(const MyVector2& mouseVelocity,float deltaTime);
protected:
	//カメラの回転処理
	void CameraRotate(const MyVector2& mouseVelocity);
	//カメラの行列を設定する
	void CameraSet();
private:
	MyVector3 m_rad;//回転角度
	//操作するか
	bool m_isControll;
protected:
	//回転なしの場合のtargetからの方向
	const MyVector3 m_defaultVelocity = MyVector3(0, 1, 0);

	//注視点
	MyVector3 m_target;
	//距離
	float m_distance;
};

#endif