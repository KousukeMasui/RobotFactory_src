#include "TitleCamera.h"
#include"CSVReader\CSVReader.h"
#include"EffekseerForDXLib.h"
#include<DxLib.h>
#include"Math/Converter.h"

//csv読み込みをしてそこを順番に進んでいく
TitleCamera::TitleCamera():
	Camera(),
	m_index(0),
	m_pointStartCol(0),
	m_radStartCol(3),
	m_lerp(0.0f)
{
	//csv読み込み　ターゲットの位置と回転角度を格納
	CSVReader csv("res/CSV/title_demo.csv");
	for (int row = 0; row < csv.rows(); row++)
	{
		m_points.push_back(MyVector3(csv.getf(row, m_pointStartCol), csv.getf(row, m_pointStartCol + 1), csv.getf(row, m_pointStartCol + 2)));

		m_rads.push_back(MyVector3(Converter::DegToRad(csv.getf(row,m_radStartCol)), Converter::DegToRad(csv.getf(row,m_radStartCol+1)), Converter::DegToRad(csv.getf(row,m_radStartCol+2))));
	}

	m_position = m_points[0];
	m_rotate = MyMatrix4::RotateZXY(m_rads[0]);

	CameraSet();
}

TitleCamera::~TitleCamera()
{
}

void TitleCamera::Update(float deltaTime)
{
	m_lerp += deltaTime / 300.0f;
	m_target = MyVector3::Lerp(m_points[m_index], m_points[(m_index + 1)%m_points.size()], m_lerp);
	m_rotate = MyMatrix4::Lerp(MyMatrix4::RotateZXY(m_rads[m_index]), MyMatrix4::RotateZXY(m_rads[(m_index + 1) % m_points.size()]), m_lerp);
	//タイマが1を超えたら
	if (m_lerp >= 1.0f)
	{
		m_lerp = 0.0f;//初期化
		m_index = (m_index + 1) % m_points.size();//indexを足す(ループさせる)
	}
	//カメラ行列を設定
	CameraSet();
}
