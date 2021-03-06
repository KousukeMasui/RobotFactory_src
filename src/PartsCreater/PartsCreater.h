#pragma once

//Partsを生成するクラス
class IWorld;
#include"Base/RoadFinder/PathFinder.h"
#include"Actor\Base\Actor3D.h"
#include"Base/GameUsing.h"
#include"Math/Point2/Point2.h"
class PartsCreater: public Actor3D
{
public:
	explicit PartsCreater(IWorld& world);
	~PartsCreater();

	void OnUpdate(float deltaTime) override;

private:
	//Partsを生成する関数
	void Create();

	//工場の周りと工場をpoint2で返す
	std::vector<Point2> GetFactoryPoints(const FactoryPtr& factory) const;
	std::vector<Point2> GetFactoryPoints(const FactoryPtrs& factorys) const;
private:
	//生成までの間隔
	float m_createInterval;
	//前回生成された位置
	MyVector3 m_prevCreatePosition;
	PathFinder m_finder;
};