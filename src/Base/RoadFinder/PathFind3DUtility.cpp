#include "PathFind3DUtility.h"
#include"Math/Vector/MyVector3.h"
#include"Math/Vector/MyVector2.h"
#include"Math\Converter.h"
const MyVector2 PathFind3DUtility::size = MyVector2(16,16);

Point2 PathFind3DUtility::ToNodePoint2(const MyVector3 & position)
{
	MyVector3 p = position - MyVector3(size.x*1.5f, 0.0f, size.y*0.5f);
	int x = 0;
	while (p.x > size.x)
	{
		p.x -= size.x;
		x++;
	}
	if (p.x > size.x / 2.0f)//�Ԃ�x��x+1�̋߂����ɂ���
	{
		x++;
	}
	int y = 0;
	while (p.z > size.y)
	{
		p.z -= size.y;
		y++;
	}
	if (p.z > size.y / 2.0f)//�Ԃ�x��x+1�̋߂����ɂ���
	{
		y++;
	}
	return Point2(x, y);
}

Point2 PathFind3DUtility::ToNodePoint2(const MyVector3& position,const PathFinder& finder)
{
	return GetNearPoint2(ToNodePoint2(position), finder);
}

std::vector<Point2> PathFind3DUtility::ToNodePoint2(Line3D line)
{
	std::vector<Point2> result;
	Point2 start = ToNodePoint2(line.m_start);
	Point2 end = ToNodePoint2(line.m_end);

	MyVector3 velocity = line.Direction().Normalize();

	MyVector3 position = line.m_start;
	Point2 point;
	do
	{
		//�T�C�Y��������
		position += velocity * size.x;
		point = ToNodePoint2(position);
		result.push_back(point);
		//���𒴂�����
		if (line.Length() <= MyVector3::Distance(line.m_start, position))
		{
			break;//�I��
		}
	} while (true);
	result.push_back(start);
	result.push_back(end);
	return result;
}

MyVector3 PathFind3DUtility::ToPosition(Point2 point)
{
	return MyVector3((point.x+1) * size.x + size.x / 2.0f, 0.0f,(point.y) * size.y + size.y / 2.0f);
}

std::vector<Point2> PathFind3DUtility::ToRoad(const std::vector<NodePtr>& nodes, const PathFinder & finder)
{
	std::vector<Point2> result;
	//�M�U�M�U�@+ �����̊Ԃɂ���o�H�_���폜
	std::vector<NodePtr> n = ToStraight(ToDiagonal(nodes, finder));
	for (auto node : n)
		result.push_back(node->position());
	return result;
}

Point2 PathFind3DUtility::GetNearPoint2(const Point2 & point, const PathFinder & finder)
{
	//�ʒu���ړ��\�̏ꍇ�A�������s��Ȃ�
	if (finder[point]->walkable())
		return point;
	int cnt = 1;
	do {
		for (int x = -cnt; x <= cnt; x++)//-1~1
		{
			for (int y = -cnt; y <= cnt; y++)//-1~1
			{
				if (std::abs(x) < cnt &&
					std::abs(y) < cnt)//���Ɍ��������m�[�h�̈ʒu�̏ꍇ
				{
					continue;
				}
				Point2 p = point + Point2(x, y);
				if (finder[p]->walkable())
					return p;
			}
		}
		cnt++;
	} while (true);
}

std::vector<NodePtr> PathFind3DUtility::ToDiagonal(const std::vector<NodePtr>& nodes, const PathFinder & finder)
{
	std::vector<NodePtr> result;
	int length = nodes.size();

	//�Z�����Ď΂߂ɐi��ł��Ȃ��ꍇ�A����nodes��Ԃ�
	if (length <= 2) return nodes;

	for (int i = 0; i < length - 2; i++)
	{
		Point2 direction = nodes[i + 2]->position() - nodes[i]->position();
		result.push_back(nodes[i]);
		if (std::abs(direction.x) == 1 && std::abs(direction.y) == 1)//�΂߂ɐi��ł���ꍇ�A
		{
			//�΂߂ɐi�ޏꍇ�A�Q�_�ɐڂ���m�[�h�������邩�m�F
			if (finder[nodes[i]->position() + Point2(direction.x, 0)]->walkable() &&
				finder[nodes[i]->position() + Point2(0, direction.y)]->walkable())
			{
				i++;//���΂�
			}
		}
	}
	return result;
}

std::vector<NodePtr> PathFind3DUtility::ToStraight(const std::vector<NodePtr>& nodes)
{
	std::vector<NodePtr> result;
	if (nodes.size() <= 1) return nodes;
	Point2 direction(0,0);
	NodePtr prevNode = nodes.front();
	for (unsigned int i = 1; i < nodes.size();i++)
	{
		Point2 d = nodes[i]->position() - prevNode->position();
		if (direction != d)//�������ς�����ꍇ
		{
			direction = d;
			result.push_back(prevNode);
		}
		prevNode = nodes[i];
	}
	return result;
}
