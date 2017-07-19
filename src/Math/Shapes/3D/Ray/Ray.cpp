#include "Ray.h"
Ray::Ray(const MyVector3& p, const MyVector3& direction):
	m_position(p),
	m_direction(MyVector3::Normalize(direction))
{

}


// 2D座標からレイを計算する

Ray Ray::CalculateRay(const MyVector2 & position, const MyMatrix4 & screen, const MyMatrix4 & projection, const MyMatrix4 & view)
{
	MyMatrix4 un_project = MyMatrix4::InverseMatrix(view * projection * screen);
	// スクリーン座標から近クリップ面のワールド座標に変換
	MyVector3 n = MyVector3(position.x, position.y, -1.0f)*un_project;
	// スクリーン座標から遠クリップ面のワールド座標に変換
	MyVector3 f = MyVector3(position.x, position.y, 1.0f)*un_project;
	// 近クリップ面から遠クリップ面に向かうレイを作成
	return Ray(n, (f - n).Normalize());
}

Ray::~Ray()
{
}

Ray Ray::Transform(const MyMatrix4 & matrix)
{
	return Ray(m_position * matrix,m_direction * matrix.GetRotationMatrix());
}
