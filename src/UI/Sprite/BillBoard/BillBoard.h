#pragma once
#include"Math/Vector/MyVector3.h"
#include"Resources.h"
class BillBoard
{
public:
	BillBoard(TEXTURE_ID id,MyVector3* position,const MyVector3& addPos,float size);
	~BillBoard();
	//íœŠÖ”@‚±‚ê‚ğg—p‚·‚éê‡‚Í•Ï”‚Ì‰Šú‰»‚ğ–Y‚ê‚¸‚É
	void Delete();
	bool IsThis(MyVector3* position);
	bool IsDelete();
	void Position(const MyVector3& addPos);
	MyVector3 GetFirstPosition() const;
	MyVector3 GetAddPosition() const;
	void Size(float size);
	void Draw();

private:
	int m_texID;
	MyVector3* m_position;
	MyVector3 m_addPos;
	const MyVector3 m_firstPosition;
	float m_size;
	bool m_isDelete;
};