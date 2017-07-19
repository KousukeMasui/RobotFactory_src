#pragma once
#include"Object/Object.h"
#include"Math/Shapes/3D/Sphere/Sphere.h"
#include"Model/Model/Model.h"
#include"Base/GameUsing.h"
#include<forward_list>
class IWorld;
//新しいカーソルクラス　これと当たっているキャラ、工場を選択できるようにする
class SelectCursor : public Object
{
public:
	explicit SelectCursor(const MyVector3& position);
	~SelectCursor();

	//更新 指定された位置までを移動する
	virtual void Update(const MyVector3& targetPosition,float deltaTime);
	//描画
	void Draw(const Color& color) const;
	//当たり判定
	UnitPtr IsCollide(IWorld& world,InfluenceID id) const;
	UnitPtr IsCollide(const UnitPtrs& units) const;
	FactoryPtr IsCollide(const FactoryPtrs& factorys) const;
	bool IsCollide(const UnitFactory* unit) const;
	Sphere GetSphere() const;
	bool IsCollide(const Sphere& sphere) const;

	//サイズ変更
	void Scale(const MyVector3& scale);
private:
	Model m_model;
	//サイズ
	MyVector3 m_scale;
protected:
	//当たり判定用球
	Sphere m_sphere;
};