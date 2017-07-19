#pragma once
#include"Math/Point2/Point2.h"
class MyVector3;
class MyVector2;
#include<vector>
#include"Math/Shapes/3D/Line/Line3D.h"
#include"Base/RoadFinder/PathFinder.h"
//PathFinder��3D�ł��g����悤�ɂ���N���X
class PathFind3DUtility
{
public:
	//Vector3���猻�݂̃m�[�h�̈ʒu�����߂�
	//size �m�[�h�̊Ԃ̒���(X,Y�ňႤ�\��������̂�Vector2)
	static Point2 ToNodePoint2(const MyVector3& position);
	//���j�b�g�̌o�H�T���ŋ߂Â������Čo�H���肩��O���ꍇ������̂ł����␳���ĕԂ�
	static Point2 ToNodePoint2(const MyVector3& position, const PathFinder& finder);
	static std::vector<Point2> ToNodePoint2(Line3D line);
	static MyVector3 ToPosition(Point2 point);

	//�o�H�T�������o�H��␳���ĕԂ�
	static std::vector<Point2> ToRoad(const std::vector<NodePtr>& nodes,const PathFinder& finder);
	static const MyVector2 size;
private:
	//�΂߂ɓ����ۂɃW�O�U�O�ɓ����̂ł��̕␳���s����node��Ԃ�
	static std::vector<NodePtr> ToDiagonal(const std::vector<NodePtr>& nodes, const PathFinder& finder);
	//node���^�������ɐi��ł���ꍇ�ɂ܂Ƃ߂�
	static std::vector<NodePtr> ToStraight(const std::vector<NodePtr>& nodes);
private:
	//3D�Ȃ̂Ŏ��X�ړ��s�̏ꏊ�ɓ����Ă��܂��̂ł��̏ꍇ�̏���
	static Point2 GetNearPoint2(const Point2& point, const PathFinder& finder);
};