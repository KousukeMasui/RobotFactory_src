#include"SceneNull.h"

#include"Scene.h"
//開始
void SceneNull::Initialize() { }
//更新
void SceneNull::Update(float deltaTime)
{
	(void)deltaTime;
}
//描画
void SceneNull::Draw()const{}
//終了しているか
bool SceneNull::IsEnd()const
{
	return false;
}
//次のシーンを返す
int SceneNull::Next()const
{
	return (int)Scene::None;
}
//終了
void SceneNull::End(){}