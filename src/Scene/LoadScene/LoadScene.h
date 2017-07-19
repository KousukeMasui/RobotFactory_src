#pragma once
#include"Scene\Base\IScene.h"
#include"UI/UIManager/UIManager.h"
//���[�h�V�[�� �񓯊��ǂݍ��݂��g���ă��[�h���s��
class LoadScene : public IScene
{
public:
	//�R���X�g���N�^
	LoadScene();
	//�f�X�g���N�^
	~LoadScene();
	void Initialize() override;//������
	void Update(float deltaTime) override;//���[�h���̍X�V����
	void Draw() const override;
	bool IsEnd() const override;
	void End() override;
	int Next()const override;
private:
	//���\�[�X�ǂݍ��݁@DxLib�ˑ��̕��̂ݗL��
	void ResourceLoad();
private:
	UIManager m_manager;
};