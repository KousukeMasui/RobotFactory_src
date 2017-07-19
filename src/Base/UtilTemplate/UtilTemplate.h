#pragma once
#include"Math/Vector/MyVector3.h"
struct UtilTemplate
{
	template<typename T>
	static T GetNearObject(const MyVector3& position, const T& t1, const T& t2, std::function<MyVector3(const T& t)> GetPosFunc)
	{
		if (MyVector3::Distance(position, GetPosFunc(t1)) <= MyVector3::Distance(position, GetPosFunc(t2)))
			return t1;
		return t2;
	}
};