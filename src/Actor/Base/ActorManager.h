#ifndef	 _ACTOR_MANAGER_H_
#define	 _ACTOR_MANAGER_H_

#include<unordered_map>
#include"ActorPtr.h"
#include"Actor3D.h"

enum class ActorGroup;
//�A�N�^�[�}�l�[�W���[
class ActorManager
{
public:
	//�R���X�g���N�^
	ActorManager();
	//������
	void Initialize();
	//�X�V
	void Update(float deltaTime);
	//�`��
	void Draw() const;
	//�A�N�^�[�̒ǉ�
	void AddActor(ActorGroup group, const ActorPtr& actor);
	//�A�N�^�[�̌���
	ActorPtr FindActor(const std::string& name);
	std::vector<ActorPtr> FindActors(const ActorGroup& group);
	//���b�Z�[�W����
	void HandleMessage(EventMessage message, void* param);
	//
	ActorManager(const ActorManager& other) = delete;
	ActorManager& operator=(const ActorManager& other) = delete;

	void Clear();
private:
	//�Փ˔���
	void Collide();
private:
	//���[�g�m�[�h
	Actor3D m_root;
	//�A�N�^�[�O���[�v
	std::unordered_map<ActorGroup, ActorPtr> m_actors;

};

#endif