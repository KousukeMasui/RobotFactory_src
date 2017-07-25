#ifndef _ACTOR_H_
#define _ACTOR_H_

#include<string>
#include<dxlib.h>
#include<functional>
#include<forward_list>
#include "ActorPtr.h"
#include"Math/Matrix/MyMatrix4.h"
#include"Math\Converter.h"
#include<vector>
#include"Math/Shapes/3D/Shape3D.h"
#include"Math/Shapes/Shapes.h"
#include<map>
#include"Model/AnimationModel/AnimationModel.h"
#include"Math/Collision/HitInfo/HitInfo.h"
class IWorld;
enum class EventMessage;

//�A�N�^�[�N���X
class Actor3D
{
public:
	//�R���X�g���N�^
	Actor3D(IWorld& world, const std::string& name, const MyVector3& position);
	

	//�R���X�g���N�^
	explicit Actor3D(const std::string& name = "none");

	//�f�X�g���N�^
	virtual ~Actor3D(){}


	//�X�V
	void Update(float deltaTime);
	//�`��
	void Draw() const;

	//�Փ˔���
	void Collide(Actor3D& other);

	//���S���Ă��邩?
	bool IsDead() const;

	//���S����
	void Dead();

	//���O��Ԃ�
	const std::string& GetName() const;

	//���W��Ԃ�
	MyVector3 GetPosition() const;
	MyVector3 GetVelocity() const;

	void SetPosition(MyVector3 sPos);
	MyMatrix4 GetRotate() const;

	std::map<Shape2DEnum, std::vector<std::shared_ptr<Shape2D>>>  GetShapes2D()const;
	std::map<Shape3DEnum, std::vector<std::shared_ptr<Shape3D>>>  GetShapes3D()const;

	//�ϊ��s���Ԃ�
	MyMatrix4 GetPose() const;

	//�q�̌���
	ActorPtr FindChildren(const std::string& name);
	//�q�̌���
	ActorPtr FindChildren(std::function<bool(const Actor3D&)>fn);

	//�q���m�̏Փ˔���
	void CollideChildren(Actor3D& other);
	//�Z�퓯�m�̏Փ˔���
	void CollideSibling();

	//�q�̒ǉ�
	void AddChild(const ActorPtr& child);
	//�S�Ă̎q�̎擾
	std::vector<ActorPtr> GetChilds();
	//�q������
	void EachChildren(std::function<void(Actor3D&)> fn);
	//�q������(const��)
	void EachChildren(std::function<void(const Actor3D&)> fn) const;

	//�q���폜����
	void RemoveChildren(std::function<bool(Actor3D& actor)>fn);
	//�q���폜����
	void RemoveChildren();
	//�q�������폜����
	void ClearChildren();
	//���b�Z�[�W����
	void HandleMessage(EventMessage message, void* param);

	void Translate(const MyVector3& velocity);

	//�R�s�[�֎~
	Actor3D(const Actor3D& other) = delete;
	Actor3D& operator=(const Actor3D& other) = delete;
private:
	//���b�Z�[�W����
	virtual void OnMessage(EventMessage message, void* param);
	//�X�V
	virtual void OnUpdate(float deltaTime);
	//�`��
	virtual void OnDraw() const;
	//�Փ˂���
	virtual void OnCollide(Actor3D& other, const HitInfo& info);

	//�Փ˔��� ���ꂼ�ꓖ���蔻�肪�قȂ�̂� �����o������������̂ň����ǉ�
	virtual bool IsCollide(const Actor3D& other,HitInfo& info)const;

protected:
	//���[���h
	IWorld*			m_world;
	//���O
	std::string		m_name;
	//���W
	MyVector3		m_position;

	//�ړ�����
	MyVector3 m_velocity;
	//��]
	
	MyMatrix4		m_rotate;
	//���S�t���O
	bool			m_isDead;
	//�����蔻��p�}�` ���G�Ȍ`�ɂ��Ή����邽�߂�vector�Ɋi�[
	std::map<Shape2DEnum, std::vector<std::shared_ptr<Shape2D>>> m_shapes2DMap;
	std::map<Shape3DEnum, std::vector<std::shared_ptr<Shape3D>>> m_shapes3DMap;
private:
	//�q�A�N�^�[
	std::forward_list<ActorPtr> children_;

};

#endif