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
	void Update(float deltaTime);
	//�o�H�T���p�N���X����
	PathFinder CreatePathFinder();

	//�o�H�T�� isPriority �D�悵�Č������邩
	void PathFind(const PathFinder& finder,const MyVector3& target,RootAgent& agent,bool isPriority=false);
	//�o�H�T�� isPriority �D�悵�Č������邩
	void PathFind(const PathFinder& finder, const std::vector<Point2>& targets,RootAgent& agent, bool isPriority = false);
private:
	Point2 ToNodePosition(const PathFinder& finder,const MyVector3& position);
	void Find();
private:
	//�o�H�T���ɕK�v�ȃf�[�^
	std::list<FindTargetData> m_findTargetData;
	std::list<FindMultiTargetData> m_findMultiTargetData;
	//�o�H�T�����s������
	std::list<FindID> m_findIDs;
	//1�b�ŉ���o�H�T�����邩
	const int m_findMaxSecond;
	//���݉��񌟍�������
	int m_nowSecondFind;
	//�t���[���^�C�}
	float m_frameTimer;
	//�m�[�h���
	FieldMap m_field;
};