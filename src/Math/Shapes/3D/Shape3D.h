#ifndef	_Shape3D_H_
#define	_Shape3D_H_

#include"Math/Vector/MyVector3.h"
#include<vector>
#include"Math/Matrix/MyMatrix4.h"
//図形の親クラス　子で使う変数を全て格納して、当たり判定を簡単に出来るようにする
class Shape3D
{
public:
	Shape3D();

	//ポリゴン用
	explicit Shape3D(const std::vector<MyVector3>& v);
	Shape3D(const MyVector3& p, const std::vector<MyVector3>& v);
	
	Shape3D(const MyVector3& p1, const MyVector3& p2, float radius);
	Shape3D(const MyVector3& p, float radius);


	//位置の設定 verticesは現在動かしていない
	virtual void Translate(const MyVector3& vec);
public:
	//位置その1	1つしか座標を持たない図形はここに座標を格納
	MyVector3 p1;
	//位置その2 線やカプセルに使用
	MyVector3 p2;
	//半径
	float radius;

	//大きさ
	MyVector3 size;

	//回転行列
	MyMatrix4 rotate;

	//ポリゴン用
	std::vector<MyVector3> vertices;
};

#endif