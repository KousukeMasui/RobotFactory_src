#ifndef	 _FIELD_H_
#define	 _FIELD_H_

#include"Model/StaticModel/StaticModel.h"
struct Line3D;

struct HitInfo;
//�|���\���̂�
//�t�B�[���h���f���̓ǂݍ��݂Ɠ����蔻��̃Z�b�g���s��
class Field
{
public:
	Field();
	~Field();

	void Update(float deltaTime);

	void Draw();
	//�n�ʂƂ̓����蔻��
	HitInfo IsCollide(const Line3D& line);
	HitInfo IsCollide(const MyVector3& p1, const MyVector3& p2);
private:
	StaticModel m_groundModel;
	//�󃂃f���f�[�^
	StaticModel m_skyModel;
	//�t�B�[���h�͈͕̔`��p���f��
	StaticModel m_clampModel;
};

#endif