#pragma once
#include"Base/FindTargetData.h"
#include<list>
#include<functional>
class RootAgent;
class FieldMap;
//経路探索を一括で行う(1フレームで複数が経路を求めてパフォーマンスの低下を防止する)
class RootFind {
private:
	enum class FindID {
		SINGLE=0,	//目的地が一つ
		MULTI		//目的地が複数
	};
public:
	RootFind();
	~RootFind();

	//更新
	void Update(float deltaTime);
	//経路探索用クラス生成
	PathFinder CreatePathFinder();

	//経路探索 isPriority 優先して検索するか
	void PathFind(const PathFinder& finder,const MyVector3& target,RootAgent& agent,bool isPriority=false);
	//経路探索 isPriority 優先して検索するか
	void PathFind(const PathFinder& finder, const std::vector<Point2>& targets,RootAgent& agent, bool isPriority = false);
private:
	Point2 ToNodePosition(const PathFinder& finder,const MyVector3& position);
	void Find();
private:
	//経路探索に必要なデータ
	std::list<FindTargetData> m_findTargetData;
	std::list<FindMultiTargetData> m_findMultiTargetData;
	//経路探索を行う順番
	std::list<FindID> m_findIDs;
	//1秒で何回経路探索するか
	const int m_findMaxSecond;
	//現在何回検索したか
	int m_nowSecondFind;
	//フレームタイマ
	float m_frameTimer;
	//ノード情報
	FieldMap m_field;
};