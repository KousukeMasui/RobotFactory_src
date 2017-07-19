#pragma once
#include "Math/Point2/Point2.h"
#include<map>

// �t�B�[���h�}�b�v�i�f�o�b�O�p�j
class FieldMap
{
public:
	// �R���X�g���N�^
	FieldMap();

	// ���̎擾
	int width() const;

	// �����̎擾
	int height() const;

	int CellSize() const;

	// �f�[�^�̎擾
	int operator [] (const Point2& position);

	void Draw() const;

private:
	// �{���̓}�b�v�f�[�^������
	std::map<int, std::map<int, int>> m_map;//[x][y]value

	int m_width;
	int m_height;
};