#ifndef	  _TITLE_SCENE_H_
#define	  _TITLE_SCENE_H_

#include"../Base/IScene.h"
#include<DxLib.h>
#include"UI/UIManager/UIManager.h"
#include<memory>
class World;
//�^�C�g���V�[��
class TitleScene :public IScene
{
public:
	//�R���X�g���N�^
	explicit TitleScene(const std::shared_ptr<World>& world);
	//�f�X�g���N�^
	~TitleScene();
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
private:
	std::shared_ptr<World> m_world;
	std::shared_ptr<UIManager> m_UIManager;

	bool m_isEnd;
};

#endif