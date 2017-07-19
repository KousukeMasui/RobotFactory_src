#pragma once
#include"Map/NodeGrid.h"

class FieldMap;
class AstarOpenList;
class DijkstraOpenList;
class RangeOpenList;
//�o�H�T���N���X
class PathFinder
{
public:
	//�R���X�g���N�^
	explicit PathFinder(FieldMap& map);

	//�ڕW�ʒu������
	std::vector<NodePtr> FindTarget(const Point2& start, const Point2& target);

	//�����̖ڕW�ʒu������
	std::vector<NodePtr> FindMultiTarget(const Point2& start);

	//�����̖ڕW�ʒu������
	std::vector<std::vector<NodePtr>> FindMultiTargetAll(const Point2& start);
	//�ړ��͈͂̌���
	void findSearchRange(const Point2& start, float cost);
	//�ڕW�n�_�̒ǉ�
	void AddTarget(const Point2& target);
	void AddTargets(const std::vector<Point2>& targets);
	//�m�[�h�̎擾
	NodePtr operator [](const Point2& position) const;
	//�����p�X�m�[�h�̍쐬
	std::vector<NodePtr> CreatePath(const Point2& target) const;

private:
	//�o�H�T���֐��e���v���[�g
	template <typename Grid, typename List, typename Node>
	static std::vector<Node> FindPath(Grid& grid, List list, const Node& start)
	{
		list.Start(start);
		while (!list.IsEmpty())
		{
			list.Pop();
			if (list.IsGoal())
			{
				return grid.createPath(list.GetFront());
			}
			grid.neighbors(list.GetFront(), [&](const Node& node) {list.Push(node); });
			//grid.draw();//�f�o�b�O�\��
		}
		return std::vector<Node>();
	}

	//�o�H�T���֐��e���v���[�g
	template <typename Grid, typename List, typename Node>
	std::vector<std::vector<Node>> FindPathAllTarget(Grid& grid, List list, const Node& start)
	{
		std::vector<std::vector<Node>> result;
		list.Start(start);
		int num = 0;
		while (!list.IsEmpty())
		{
			list.Pop();
			if (list.IsGoal())
			{
				result.push_back(grid.createPath(list.GetFront()));
				num++;
				//�S�Ẵ^�[�Q�b�g�܂ł̓�����ꂽ��
				if (targetNum <= num)
					break;
			}
			grid.neighbors(list.GetFront(), [&](const Node& node) {list.Push(node); });
			//grid.draw();//�f�o�b�O�\��
		}
		return result;
	}


private:
	//�p�X�����p�i�q�m�[�h
	NodeGrid m_grid;

	int targetNum;
};