#ifndef	 _SCENE_MANAGER_H_
#define	 _SCENE_MANAGER_H_

enum class Scene;
#include"IScenePtr.h"
#include<unordered_map>
#include"UI/Sprite/Base/SpritePtr.h"
#include"Base/Manager/State/StateManager.h"
//�V�[���}�l�[�W���[
class SceneManager
{
public:
	//�R���X�g���N�^
	SceneManager();
	//������
	void Initialize();
	//�X�V
	void Update(float deltaTime);

	//�`��
	void Draw();

	//�V�[���̒ǉ�
	void Add(Scene name, const IScenePtr& scene);
	//�V�[���̕ύX
	void Change(Scene scene);

	//�R�s�[�֎~
	SceneManager(const SceneManager& other) = delete;
	SceneManager operator=(const SceneManager& other) = delete;
private:
	//�V�[��������X�e�[�g�}�l�[�W���[
	StateManager m_manager;
	SpritePtr m_fadeSprite;
};

#endif