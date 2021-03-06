#pragma once
#include"Math/Vector/MyVector3.h"
#include"Resources.h"
class BillBoard
{
public:
	BillBoard(TEXTURE_ID id,MyVector3* position,const MyVector3& addPos,float size);
	~BillBoard();
	//削除関数　これを使用する場合は変数の初期化を忘れずに
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