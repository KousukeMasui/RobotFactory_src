#include "BillBoard.h"
#include"Loader\Loader.h"
#include<DxLib.h>
#include"Math/Converter.h"
BillBoard::BillBoard(TEXTURE_ID id, MyVector3* position,const MyVector3& addPos, float size):
	m_texID(Loader::GetInstance().TextureHandle(id)),
	m_position(position),
	m_addPos(addPos),
	m_firstPosition(addPos),
	m_size(size),
	m_isDelete(false)
{
}

BillBoard::~BillBoard()
{
}

void BillBoard::Delete()
{
	m_isDelete = true;
}

bool BillBoard::IsThis(MyVector3 * position)
{
	return m_position == position;
}

bool BillBoard::IsDelete()
{
	return m_isDelete;
}

void BillBoard::Position(const MyVector3 & addPos)
{
	m_addPos = addPos;
}

MyVector3 BillBoard::GetFirstPosition() const
{
	return m_firstPosition;
}

MyVector3 BillBoard::GetAddPosition() const
{
	return m_addPos;
}

void BillBoard::Size(float size)
{
	m_size = size;
}

void BillBoard::Draw()
{
	DrawBillboard3D(Converter::MyVector3ToVECTOR(*m_position + m_addPos), 0.5f, 0.5f, m_size, 0.0f, m_texID, true, false);
}
