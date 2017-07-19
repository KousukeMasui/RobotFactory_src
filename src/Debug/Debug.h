#pragma once

class World;
class FollowCamera;
#include<memory>
#include"Model/Model/Model.h"
#include"Base/GameUsing.h"
class LerpCursor;
enum class CameraTarget
{
	UNIT,
	CURSOR
};

//�f�o�b�O���[�h�̍ۂ̃J�����̐ݒ��`����s���N���X
class Debug
{
public:
	//�R���X�g���N�^
	Debug(World& world,LerpCursor& cursor);
	//�f�X�g���N�^
	~Debug();
	//���݃f�o�b�O����
	bool IsDebug();
	//�X�V
	void Update(float deltaTime);
	//�`��
	void Draw() const;
private:
	//�f�o�b�O����������
	void Init();
	//�f�o�b�O�I���֐�
	void End();
	//�f�o�b�O�؂�ւ�
	void ChangeDebug();
	//���j�b�g�؂�ւ�
	void ChangeUnit();
	//�J�����̃^�[�Q�b�g��ύX����a
	void CameraTargetChange();
private:
	World& m_world;
	std::shared_ptr<FollowCamera> m_camera;
	bool m_isDebug;//�f�o�b�O��true
	UnitPtr m_targetUnit;
	Model m_unitTarget;
	CameraTarget m_target;
	LerpCursor& m_cursor;
};