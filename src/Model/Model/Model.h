#pragma once

#include"../ParentModel.h"

#include"Math/Color/Color.h"
//通常モデル アニメーションがなく、かつ移動し続けるモデルに使用して下さい。
class Model : public ParentModel
{
public:
	explicit Model(MODEL_ID id);
	~Model();
	//描画
	void Draw(const MyVector3& position) const;
	void Draw(const MyVector3& position, const MyVector3& scale, const MyMatrix4& rotate) const;
	void Draw(const MyVector3& position, const MyVector3& scale, const MyVector3& rad) const;
	void Draw(const MyMatrix4& pose) const;


};