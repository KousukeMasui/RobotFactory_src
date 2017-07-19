#pragma once
#include"../ParentModel.h"
//��ؓ����Ȃ����f��
class StaticModel : public ParentModel
{
public:
	StaticModel(MODEL_ID id,bool isOnce,const MyVector3& position,const MyVector3& scale,const MyVector3& rad);
	StaticModel(MODEL_ID id,bool isOnce,const MyVector3& position,const MyVector3& scale,const MyMatrix4& rotate);
	StaticModel(MODEL_ID id,bool isOnce,const MyMatrix4& pose);
	~StaticModel();


	//�����蔻��Z�b�g�֐�
	///<summary>���f���̓����蔻��̐ݒ�</summary>
	///<param name='divisionX'>X���̕�����</param>
	///<param name='divisionY'>Y���̕�����</param>
	///<param name='divisionZ'>Z���̕�����</param>
	void CollideSet(int divisionX, int divisionY, int divisionZ);
	//�����蔻��̍X�V Update�̍Ō�ɓ���������
	void CollideUpdate();
	//�����蔻��̍폜
	void CollideDelete();

	void Draw() const;
};