#ifndef	 _FIELD_H_
#define	 _FIELD_H_

#include"Model/StaticModel/StaticModel.h"
struct Line3D;

struct HitInfo;
//板ポリ表示のみ
//フィールドモデルの読み込みと当たり判定のセットを行う
class Field
{
public:
	Field();
	~Field();

	void Update(float deltaTime);

	void Draw();
	//地面との当たり判定
	HitInfo IsCollide(const Line3D& line);
	HitInfo IsCollide(const MyVector3& p1, const MyVector3& p2);
private:
	StaticModel m_groundModel;
	//空モデルデータ
	StaticModel m_skyModel;
	//フィールドの範囲描画用モデル
	StaticModel m_clampModel;
};

#endif