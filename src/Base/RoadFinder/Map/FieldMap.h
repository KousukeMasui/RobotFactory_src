#pragma once
#include "Math/Point2/Point2.h"
#include<map>

// フィールドマップ（デバッグ用）
class FieldMap
{
public:
	// コンストラクタ
	FieldMap();

	// 幅の取得
	int width() const;

	// 高さの取得
	int height() const;

	int CellSize() const;

	// データの取得
	int operator [] (const Point2& position);

	void Draw() const;

private:
	// 本来はマップデータを持つ
	std::map<int, std::map<int, int>> m_map;//[x][y]value

	int m_width;
	int m_height;
};