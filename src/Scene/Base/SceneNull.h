#ifndef	_SCENE_NULL_H_
#define	_SCENE_NULL_H_

#include"IScene.h"

//��̃V�[��
class SceneNull :public IScene
{
public:
	//�J�n
	virtual void Initialize()override;
	//�X�V
	virtual void Update(float deltaTime)override;
	//�`��
	virtual void Draw()const override;
	//�I�����Ă��邩
	virtual bool IsEnd()const override;
	//���̃V�[����Ԃ�
	virtual int Next()const override;
	//�I��
	virtual void End() override;
};

#endif