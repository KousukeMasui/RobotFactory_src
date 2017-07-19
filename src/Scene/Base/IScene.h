#ifndef	_ISCENE_H_
#define	_ISCENE_H_

enum class Scene;
#include"Base/Manager/State/IState.h"
//�V�[���C���^�[�t�F�[�X
class IScene : public IState
{
public:
	//���z�f�X�g���N�^
	virtual ~IScene(){}
	//�Q�[���J�n
	virtual void Initialize() = 0;
	//�X�V
	virtual void Update(float deltaTime) = 0;
	//�`��
	virtual void Draw()const = 0;
	//�I�����Ă��邩
	virtual bool IsEnd()const = 0;
	//���̃V�[����Ԃ�
	virtual int Next()const = 0;
	//�I��
	virtual void End() = 0;


	/*
	*/
};

#endif