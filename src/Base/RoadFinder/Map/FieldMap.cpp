#include "FieldMap.h"
#include"CSVReader\CSVReader.h"
//width,heightの戻り値の数だけ生成する csvのサイズを後で与える
// コンストラクタ
FieldMap::FieldMap()
{
	//工場設置前のステージを取得
	CSVReader csv("res/CSV/nodeMap.csv");
	//m_mapにcsvのデータを全て書き込む
	csv.AllFunction([&](int row,int colum)
	{
		m_map[colum][row] = csv.geti(row, colum);
	});
	m_width = csv.colums();
	m_height = csv.rows();
}

// 幅の取得

int FieldMap::width() const
{
	return m_width;
}

// 高さの取得

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
