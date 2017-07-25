#pragma once
#include"Base/FindTargetData.h"
#include<list>
#include<functional>
class RootAgent;
class FieldMap;
//�o�H�T�����ꊇ�ōs��(1�t���[���ŕ������o�H�����߂ăp�t�H�[�}���X�̒ቺ��h�~����)
class RootFind {
private:
	enum class FindID {
		SINGLE=0,	//�ړI�n�����
		MULTI		//�ړI�n������
	};
public:
	RootFind();
	~RootFind();

	//�X�V
	void Update();
	//�o�H�T���p�N���X����
	PathFinder CreatePathFinder();

	//�o�H�T��
	void PathFind(const PathFinder& finder,const MyVector3& target,RootAgent& agent);
	//�o�H�T��
	void PathFind(const PathFinder& finder, const std::vector<Point2>& targets,RootAgent& agent);
private:
	Point2 ToNodePosition(const PathFinder& finder,const MyVector3& position);
	void Find();
private:
	//�o�H�T���ɕK�v�ȃf�[�^
	std::list<FindTargetData> m_findTargetData;
	std::list<FindMultiTargetData> m_findMultiTargetData;
	//�o�H�T�����s������
	std::list<FindID> m_findIDs;
	//1�t���[���ŉ���o�H�T�����邩
	const int m_findMax;
	//�m�[�h���
	FieldMap m_field;
};