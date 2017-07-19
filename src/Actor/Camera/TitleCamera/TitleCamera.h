#pragma once

#include"../Camera.h"
#include<vector>
class TitleCamera : public Camera
{
public:
	TitleCamera();
	~TitleCamera();

	virtual void Update(float deltaTime) override;

private:
	//目的地の配列
	std::vector<MyVector3> m_points;
	//目的地に着いた時の回転角度
	std::vector<MyVector3> m_rads;

	//現在の配列のインデックス
	int m_index;
	//leap数値
	float m_lerp;
	//csvの位置
	const int m_pointStartCol;
	const int m_radStartCol;
};