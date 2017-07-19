#pragma once

#include"Resources.h"
#include"Model/StaticModel/StaticModel.h"
#include"Math/Shapes/3D/Shape3D.h"
#include<memory>
#include"Math/Collision/HitInfo/HitInfo.h"
class Object
{
public:
	Object(const MyVector3& position, const MyMatrix4& rotate);
	virtual ~Object() {}
	//位置
	MyVector3 Position() const;
	MyVector3* PositionPtr();
	void Position(const MyVector3& position);
	//回転
	MyMatrix4 Rotate() const;
	void Rotate(const MyMatrix4& rotate);
	MyMatrix4 GetPose() const;
	//メッセージ関数
	virtual void Message(int messageID, void* data) {};
protected:
	MyVector3 m_position;
	MyMatrix4 m_rotate;

};