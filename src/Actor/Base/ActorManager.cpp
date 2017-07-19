#include"ActorManager.h"
#include"ActorGroup.h"

ActorManager::ActorManager()
{
	Initialize();
}
//������
void ActorManager::Initialize()
{
	m_actors[ActorGroup::Box] = std::make_shared<Actor3D>();
	m_actors[ActorGroup::PARTS] = std::make_shared<Actor3D>();
	m_actors[ActorGroup::PARTS_CREATER] = std::make_shared<Actor3D>();

	m_root.AddChild(m_actors[ActorGroup::Box]);
	m_root.AddChild(m_actors[ActorGroup::PARTS]);
	m_root.AddChild(m_actors[ActorGroup::PARTS_CREATER]);
}
//�X�V
void ActorManager::Update(float deltaTime)
{
	m_root.Update(deltaTime);
	Collide();
	m_root.RemoveChildren();

}
//�`��
void ActorManager::Draw() const
{
	m_root.Draw();
}
//�A�N�^�[�̒ǉ�
void ActorManager::AddActor(ActorGroup group, const ActorPtr& actor)
{
	m_actors[group]->AddChild(actor);
}

//�A�N�^�[�̌���
ActorPtr ActorManager::FindActor(const std::string& name)
{
	return m_root.FindChildren(name);
}

std::vector<ActorPtr> ActorManager::FindActors(const ActorGroup & group)
{
	return m_actors[group]->GetChilds();
}

//���b�Z�[�W����
void ActorManager::HandleMessage(EventMessage message, void* param)
{
	m_root.HandleMessage(message, param);
}
void ActorManager::Clear()
{
	m_root.ClearChildren();
}
//�Փ˔���
void ActorManager::Collide()
{
	//m_actors[ActorGroup::Box]->CollideChildren(*m_actors[ActorGroup::Player]);
}
