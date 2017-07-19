#pragma once
#include"SelectCursor.h"
//èôÅXÇ…í«è]
class LerpCursor : public SelectCursor
{
public:
	explicit LerpCursor(const MyVector3& position);
	~LerpCursor();

	void Update(const MyVector3& position,float deltaTime) override;
private:
};