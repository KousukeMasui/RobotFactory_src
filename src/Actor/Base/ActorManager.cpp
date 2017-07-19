#include"ActorManager.h"
#include"ActorGroup.h"

ActorManager::ActorManager()
{
	Initialize();
}
//初期化
void ActorManager::Initialize()
{
	m_actors[ActorGroup::Box] = std::make_shared<Actor3D>();
	m_actors[ActorGroup::PARTS] = std::make_shared<Actor3D>();
	m_actors[ActorGroup::PARTS_CREATER] = std::make_shared<Actor3D>();

	m_root.AddChild(m_actors[ActorGroup::Box]);
	m_root.AddChild(m_actors[ActorGroup::PARTS]);
	m_root.AddChild(m_actors[ActorGroup::PARTS_CREATER]);
}
//更新
void ActorManager::Update(float deltaTime)
{
	m_root.Update(deltaTime);
	Collide();
	m_root.RemoveChildren();

}
//描画
void ActorManager::Draw() const
{
	m_root.Draw();
}
//アクターの追加
void ActorManager::AddActor(ActorGroup group, const ActorPtr& actor)
{
	m_actors[group]->AddChild(actor);
}

//アクターの検索
ActorPtr ActorManager::FindActor(const std::string& name)
{
	return m_root.FindChildren(name);
}

std::vector<ActorPtr> ActorManager::FindActors(const ActorGroup & group)
{
	return m_actors[group]->GetChilds();
}

//メッセージ処理
void ActorManager::HandleMessage(EventMessage message, void* param)
{
	m_root.HandleMessage(message, param);
}
void ActorManager::Clear()
{
	m_root.ClearChildren();
}
//衝突判定
void ActorManager::Collide()
{
	//m_actors[ActorGroup::Box]->CollideChildren(*m_actors[ActorGroup::Player]);
}
