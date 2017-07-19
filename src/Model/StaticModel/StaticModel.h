#pragma once
#include"../ParentModel.h"
//一切動かないモデル
class StaticModel : public ParentModel
{
public:
	StaticModel(MODEL_ID id,bool isOnce,const MyVector3& position,const MyVector3& scale,const MyVector3& rad);
	StaticModel(MODEL_ID id,bool isOnce,const MyVector3& position,const MyVector3& scale,const MyMatrix4& rotate);
	StaticModel(MODEL_ID id,bool isOnce,const MyMatrix4& pose);
	~StaticModel();


	//当たり判定セット関数
	///<summary>モデルの当たり判定の設定</summary>
	///<param name='divisionX'>X軸の分割量</param>
	///<param name='divisionY'>Y軸の分割量</param>
	///<param name='divisionZ'>Z軸の分割量</param>
	void CollideSet(int divisionX, int divisionY, int divisionZ);
	//当たり判定の更新 Updateの最後に動かすこと
	void CollideUpdate();
	//当たり判定の削除
	void CollideDelete();

	void Draw() const;
};