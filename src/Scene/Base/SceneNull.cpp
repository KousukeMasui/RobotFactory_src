#include"SceneNull.h"

#include"Scene.h"
//�J�n
void SceneNull::Initialize() { }
//�X�V
void SceneNull::Update(float deltaTime)
{
	(void)deltaTime;
}
//�`��
void SceneNull::Draw()const{}
//�I�����Ă��邩
bool SceneNull::IsEnd()const
{
	return false;
}
//���̃V�[����Ԃ�
int SceneNull::Next()const
{
	return (int)Scene::None;
}
//�I��
void SceneNull::End(){}