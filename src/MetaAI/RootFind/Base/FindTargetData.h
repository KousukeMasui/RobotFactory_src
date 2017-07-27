#pragma once
#include"FindMultiTargetData.h"

struct FindTargetData : public FindMultiTargetData{
	FindTargetData(const PathFinder& f,RootAgent& agent, const MyVector3& target) :
		FindMultiTargetData(f,agent),
		target(target)
	{

	}
	const MyVector3 target;
};