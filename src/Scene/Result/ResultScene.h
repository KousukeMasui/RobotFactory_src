#pragma once


#include"../Base/IScene.h"
#include<DxLib.h>
class World;
#include<memory>
#include"UI/UIManager/UIManager.h"
//�^�C�g���V�[��
class ResultScene :public IScene
{
public:
	//�R���X�g���N�^
	explicit ResultScene(const std::shared_ptr<World>& world,bool& isWin);
	//�f�X�g���N�^
	~ResultScene();
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
	bool& m_isWin;
	bool m_isEnd;
	Scene m_nextScene;
};