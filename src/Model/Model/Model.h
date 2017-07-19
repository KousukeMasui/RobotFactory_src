#pragma once

#include"../ParentModel.h"

#include"Math/Color/Color.h"
//�ʏ탂�f�� �A�j���[�V�������Ȃ��A���ړ��������郂�f���Ɏg�p���ĉ������B
class Model : public ParentModel
{
public:
	explicit Model(MODEL_ID id);
	~Model();
	//�`��
	void Draw(const MyVector3& position) const;
	void Draw(const MyVector3& position, const MyVector3& scale, const MyMatrix4& rotate) const;
	void Draw(const MyVector3& position, const MyVector3& scale, const MyVector3& rad) const;
	void Draw(const MyMatrix4& pose) const;


};