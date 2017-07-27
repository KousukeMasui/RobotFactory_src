#include "RootFind.h"
#include"Base/RoadFinder/PathFind3DUtility.h"
#include"RootAgent.h"
RootFind::RootFind():
	m_field(),
	m_findMaxSecond(3),
	m_frameTimer(0.0f),
	m_nowSecondFind(0)
{
}
RootFind::~RootFind()
{
}
void RootFind::Update(float deltaTime)
{
	m_frameTimer += deltaTime;
	if (m_frameTimer >= 60.0f)
	{
		m_frameTimer = 0.0f;
		m_nowSecondFind = 0;
	}
	Find();
}

PathFinder RootFind::CreatePathFinder()
{
	return PathFinder(m_field);
}

void RootFind::PathFind(const PathFinder & finder, const MyVector3 & target, RootAgent& agent)
{
	//���ɓo�^�ς݂̏ꍇ�o�^���Ȃ�
	for (auto fData : m_findTargetData) {
		if (&fData.agent == &agent) return;
	}
	agent.StartFind();
	m_findTargetData.push_back(FindTargetData(finder, agent, target));
	m_findIDs.push_back(FindID::SINGLE);
}

void RootFind::PathFind(const PathFinder & finder, const std::vector<Point2>& targets, RootAgent& agent)
{
	//���ɓo�^�ς݂̏ꍇ�o�^���Ȃ�
	for (auto fData : m_findMultiTargetData) {
		if (&fData.agent == &agent) return;
	}
	agent.StartFind();
	PathFinder f = finder;
	f.AddTargets(targets);
	m_findMultiTargetData.push_back(FindMultiTargetData(f, agent));

	m_findIDs.push_back(FindID::MULTI);
}

Point2 RootFind::ToNodePosition(const PathFinder& finder, const MyVector3 & position)
{
	Point2 result = PathFind3DUtility::ToNodePoint2(position);
	//�ړ��ł��Ȃ��}�X�ɓ����Ă��܂����ꍇ
	if (!finder[result]->walkable()) {
		result = PathFind3DUtility::ToNodePoint2(position, finder);
	}
	return result;
}

void RootFind::Find()
{
	int cnt = 0;
	for (auto idItr = m_findIDs.begin(); idItr != m_findIDs.end(); idItr++)
	{
		if (m_nowSecondFind >= m_findMaxSecond) break;
		m_nowSecondFind++;
		cnt++;
		std::vector<NodePtr> nodes;
		FindMultiTargetData* data;
		if (*idItr == FindID::SINGLE)//�P�̖ړI�n�p
		{
			auto& findData = m_findTargetData.front();
			Point2 start = ToNodePosition(findData.finder, *(findData.agent.Position()));
			Point2 target = ToNodePosition(findData.finder, findData.target);
			nodes = findData.finder.FindTarget(start, target);
			data = &findData;//�A�b�v�L���X�g
		}
		else
		{
			data = &m_findMultiTargetData.front();
			Point2 start = ToNodePosition(data->finder, *(data->agent.Position()));
			nodes = data->finder.FindMultiTarget(start);
		}
		auto root = PathFind3DUtility::ToRoad(nodes, data->finder);
		std::vector<MyVector3> result;
		for (auto point : root)
			result.push_back(PathFind3DUtility::ToPosition(point));
		data->agent.SetRoot(result);
		data->isEnd = true;
		//�v�f�폜
		m_findTargetData.remove_if([](FindTargetData& data) {return data.isEnd; });
		m_findMultiTargetData.remove_if([](FindMultiTargetData& data) {return data.isEnd; });
	}
	//�v�f�폜
	for (int i = 0; i < cnt;i++)
		m_findIDs.pop_front();
}