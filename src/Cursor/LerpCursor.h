#pragma once
#include"SelectCursor.h"
//���X�ɒǏ]
class LerpCursor : public SelectCursor
{
public:
	explicit LerpCursor(const MyVector3& position);
	~LerpCursor();

	void Update(const MyVector3& position,float deltaTime) override;
private:
};