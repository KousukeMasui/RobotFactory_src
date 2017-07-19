#ifndef	  _TITLE_SCENE_H_
#define	  _TITLE_SCENE_H_

#include"../Base/IScene.h"
#include<DxLib.h>
#include"Sprite\Sprite.h"
#include"Sprite\Base\SpriteManager.h"
//�^�C�g���V�[��
class TutoRealScene :public IScene
{
public:
	//�R���X�g���N�^
	TutoRealScene();
	//�f�X�g���N�^
	~TutoRealScene();

	//�J�n
	virtual void Start()override;

	//�X�V
	virtual void Update(float deltaTime)override;

	//�`��
	virtual void Draw()const override;

	//�I�����Ă��邩
	virtual bool IsEnd()const override;

	//���̃V�[����Ԃ�
	virtual Scene Next()const override;

	//�I��
	virtual void End() override;
private:

	std::shared_ptr<SpriteManager> m_spriteManager;

	bool m_isEnd;
};

#endif