#include "PathFinder.h"

#include"Map/FieldMap.h"
#include"List/AstarOpenList.h"
#include"List/DijkstraOpenList.h"
#include"List/RangeOpenList.h"
//�R���X�g���N�^

PathFinder::PathFinder(FieldMap & map) :
	m_grid(map),
	targetNum(0)
{

}

//�ڕW�ʒu������

std::vector<NodePtr> PathFinder::FindTarget(const Point2 & start, const Point2 & target)
{
	AstarOpenList list(m_grid[target]);
	return FindPath(m_grid, list, m_grid[start]);
}

//�����̖ڕW�ʒu������

std::vector<NodePtr> PathFinder::FindMultiTarget(const Point2 & start)
{
	DijkstraOpenList list;
	return FindPath(m_grid, list, m_grid[start]);
}

//�ړ��͈͂̌���

void PathFinder::findSearchRange(const Point2 & start, float cost)
{
	RangeOpenList list(cost);
	list.Start(m_grid[start]);
	while (!list.IsEmpty())
	{
		list.Pop();
		m_grid.neighbors(list.GetFront(), [&](const NodePtr& node) {list.Push(node); });
		//m_grid.draw();//�f�o�b�O�\��
	}
}

//�ڕW�n�_�̒ǉ�

void PathFinder::AddTarget(const Point2 & target)
{
	m_grid[target]->TargetSet();
	targetNum++;
}
void PathFinder::AddTargets(const std::vector<Point2>& targets)
{
	for (auto target : targets)
	{
		AddTarget(target);
	}
}
//�m�[�h�̎擾
NodePtr PathFinder::operator [](const Point2& position) const
{
	return m_grid[position];
}

//�����p�X�m�[�h�̍쐬

std::vector<NodePtr> PathFinder::CreatePath(const Point2 & target) const
{
	return m_grid.createPath(m_grid[target]);
}
