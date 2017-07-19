#pragma once

//追従カメラ 位置の参照ポインタを取得してそれに追従する
#include"Actor\Camera\Camera.h"
#include<functional>
class FollowCamera : public Camera
{
public:
	explicit FollowCamera();
	~FollowCamera();

	void Update(float deltaTime) override;

	void SetTarget(std::function <MyVector3()> getPositionFunc);

private:
	//位置を取得するラムダ式
	std::function <MyVector3()> m_getPositionFunc;
};