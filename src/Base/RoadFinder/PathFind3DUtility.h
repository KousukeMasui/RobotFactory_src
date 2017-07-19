#pragma once
#include"Math/Point2/Point2.h"
class MyVector3;
class MyVector2;
#include<vector>
#include"Math/Shapes/3D/Line/Line3D.h"
#include"Base/RoadFinder/PathFinder.h"
//PathFinderを3Dでも使えるようにするクラス
class PathFind3DUtility
{
public:
	//Vector3から現在のノードの位置を求める
	//size ノードの間の長さ(X,Yで違う可能性があるのでVector2)
	static Point2 ToNodePoint2(const MyVector3& position);
	//ユニットの経路探索で近づきすぎて経路判定から外れる場合があるのでそれを補正して返す
	static Point2 ToNodePoint2(const MyVector3& position, const PathFinder& finder);
	static std::vector<Point2> ToNodePoint2(Line3D line);
	static MyVector3 ToPosition(Point2 point);

	//経路探索した経路を補正して返す
	static std::vector<Point2> ToRoad(const std::vector<NodePtr>& nodes,const PathFinder& finder);
	static const MyVector2 size;
private:
	//斜めに動く際にジグザグに動くのでその補正を行ってnodeを返す
	static std::vector<NodePtr> ToDiagonal(const std::vector<NodePtr>& nodes, const PathFinder& finder);
	//nodeが真っすぐに進んでいる場合にまとめる
	static std::vector<NodePtr> ToStraight(const std::vector<NodePtr>& nodes);
private:
	//3Dなので時々移動不可の場所に入ってしまうのでその場合の処理
	static Point2 GetNearPoint2(const Point2& point, const PathFinder& finder);
};