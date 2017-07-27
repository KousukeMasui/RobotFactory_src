#pragma once
#include"Math/Vector/MyVector3.h"
#include"Base/RoadFinder/PathFinder.h"
class RootAgent;
struct FindMultiTargetData{
	FindMultiTargetData(const PathFinder& f,RootAgent& agent) :
		finder(f),
		agent(agent),
		isEnd(false)
	{

	}
	PathFinder finder;
	RootAgent& agent;
	bool isEnd;
};