#include "FieldMap.h"
#include"CSVReader\CSVReader.h"
//width,height�̖߂�l�̐������������� csv�̃T�C�Y����ŗ^����
// �R���X�g���N�^
FieldMap::FieldMap()
{
	//�H��ݒu�O�̃X�e�[�W���擾
	CSVReader csv("res/CSV/nodeMap.csv");
	//m_map��csv�̃f�[�^��S�ď�������
	csv.AllFunction([&](int row,int colum)
	{
		m_map[colum][row] = csv.geti(row, colum);
	});
	m_width = csv.colums();
	m_height = csv.rows();
}

// ���̎擾

int FieldMap::width() const
{
	return m_width;
}

// �����̎擾

int FieldMap::height() const
{
	return m_height;
}
int FieldMap::operator [] (const Point2& position)
{
	return m_map[position.x][position.y];
}

void FieldMap::Draw() const
{
}
