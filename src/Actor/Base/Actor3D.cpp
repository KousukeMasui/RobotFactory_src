#include"Actor3D.h"

#include"IWorld.h"
#include<algorithm>
#include"Math/Collision/Collision3D.h"
//�R���X�g���N�^
Actor3D::Actor3D(IWorld& world, const std::string& name, const MyVector3& position):
	m_world(&world),
	m_name(name),
	m_position(position),
	m_rotate(MyMatrix4::Identity()),
	m_isDead(false),
	m_velocity({ 0, 0, 0 })
{
}
//�R���X�g���N�^
Actor3D::Actor3D(const std::string& name)
:m_world(nullptr),
m_name(name),
m_position(MyVector3(0.0f, 0.0f, 0.0f)),
m_rotate(MyMatrix4::Identity()),
m_isDead(false),
m_velocity(MyVector3( 0, 0, 0 ))
{
}

//�X�V
void Actor3D::Update(float deltaTime)
{
	OnUpdate(deltaTime);
	EachChildren([&](Actor3D& actor){actor.Update(deltaTime); });
}
//�`��
void Actor3D::Draw() const
{
	OnDraw();
	EachChildren([&](const Actor3D& actor){actor.Draw(); });
}

//�Փ˔���
void Actor3D::Collide(Actor3D& other)
{
	HitInfo info;
	if (IsCollide(other,info))
	{
		OnCollide(other, info);
		other.OnCollide(*this, info);
	}
	EachChildren([&](Actor3D& actor){actor.Collide(other); });
}

//���S���Ă��邩?
bool Actor3D::IsDead() const
{
	return m_isDead;
}

//���S����
void Actor3D::Dead()
{
	m_isDead = true;
}

//���O��Ԃ�
const std::string& Actor3D::GetName() const
{
	return m_name;
}

//���W��Ԃ�
MyVector3 Actor3D::GetPosition() const
{
	return m_position;
}

MyVector3 Actor3D::GetVelocity() const
{
	return m_velocity;
}

void Actor3D::SetPosition(MyVector3 sPos)
{
	for (auto shape : m_shapes3DMap[Shape3DEnum::SPHERE_3D])
	{
		shape->Translate(sPos - m_position);
	}

	for (auto shape : m_shapes3DMap[Shape3DEnum::CAPSULE_3D])
	{
		shape->Translate(sPos - m_position);
	}
	m_position = sPos;
}

MyMatrix4 Actor3D::GetRotate() const
{
	return m_rotate;
}

std::map<Shape2DEnum, std::vector<std::shared_ptr<Shape2D>>> Actor3D::GetShapes2D() const
{
	return m_shapes2DMap;
}

std::map<Shape3DEnum, std::vector<std::shared_ptr<Shape3D>>> Actor3D::GetShapes3D() const
{
	return m_shapes3DMap;
}

//�ϊ��s���Ԃ�
MyMatrix4 Actor3D::GetPose() const
{
	MyMatrix4 result = m_rotate;

	return result*MyMatrix4::Translate(m_position);

	//return result.SetPosition(m_position);//Matrix4(m_rotate).setPosition(m_position);
}

//�q�̌���
ActorPtr Actor3D::FindChildren(const std::string& name)
{
	return FindChildren(
		[&](const Actor3D& actor){return actor.GetName() == name; });
}
//�q�̌���
ActorPtr Actor3D::FindChildren(std::function<bool(const Actor3D&)>fn)
{
	auto i = std::find_if(children_.begin(), children_.end(),
		[&](const ActorPtr& child){return fn(*child); });

	if (i != children_.end())
	{
		return *i;
	}
	for (auto child : children_)
	{
		auto actor = child->FindChildren(fn);
		if (actor != nullptr)
		{
			return actor;
		}
	}
	return nullptr;
}

//�q���m�̏Փ˔���
void Actor3D::CollideChildren(Actor3D& other)
{
	EachChildren([&](Actor3D& my){
		other.EachChildren([&](Actor3D& target){
			my.Collide(target); });
	});
}

//�Z�퓯�m�̏Փ˔���
void Actor3D::CollideSibling()
{
	for (auto i = children_.begin(); i != children_.end(); ++i)
	{
		std::for_each(std::next(i), children_.end(),
			[&](const ActorPtr& actor){(*i)->Collide(*actor); });
	}
}

//�q�̒ǉ�
void Actor3D::AddChild(const ActorPtr& child)
{
	children_.push_front(child);
}
std::vector<ActorPtr> Actor3D::GetChilds()
{
	std::vector<ActorPtr> result;
	for (auto child : children_)
	{
		result.push_back(child);
	}
	return result;
}
//�q������
void Actor3D::EachChildren(std::function<void(Actor3D&)> fn)
{
	std::for_each(children_.begin(), children_.end(),
		[&](const ActorPtr& actor) { fn(*actor); });
}
//�q������(const��)
void Actor3D::EachChildren(std::function<void(const Actor3D&)> fn) const
{
	std::for_each(children_.begin(), children_.end(),
		[&](const ActorPtr& actor) { fn(*actor); });
}

//�q���폜����
void Actor3D::RemoveChildren(std::function<bool(Actor3D& actor)>fn)
{
	children_.remove_if([&](ActorPtr& actor){return fn(*actor); });
}
//�q���폜����
void Actor3D::RemoveChildren()
{
	RemoveChildren([](Actor3D& actor){return actor.IsDead(); });
	EachChildren([](Actor3D& actor){actor.RemoveChildren(); });
}
//�q�������폜����
void Actor3D::ClearChildren()
{
	children_.clear();
}
//���b�Z�[�W����
void Actor3D::HandleMessage(EventMessage message, void* param)
{
	OnMessage(message, param);
	EachChildren([&](Actor3D& child){child.HandleMessage(message, param); });
}

//���b�Z�[�W����
void Actor3D::OnMessage(EventMessage message, void* param)
{
	(void)message;
	(void)param;
}

//�X�V
void Actor3D::OnUpdate(float deltaTime)
{
	(void)deltaTime;
}
//�`��
void Actor3D::OnDraw() const
{
	//body_.translate(m_position).draw();//�f�o�b�O�\��
}
//�Փ˂���
void Actor3D::OnCollide(Actor3D& other, const HitInfo& info)
{
	(void)other;
	Dead();
}
void Actor3D::Translate(const MyVector3 & velocity)
{
	m_position += velocity;
	unsigned int size = m_shapes3DMap[Shape3DEnum::CAPSULE_3D].size();
	for (unsigned int i = 0; i < size; i++)
	{
		m_shapes3DMap[Shape3DEnum::CAPSULE_3D][i]->Translate(velocity);
	}
	size = m_shapes3DMap[Shape3DEnum::SPHERE_3D].size();
	for (unsigned int i = 0; i < size; i++)
	{
		m_shapes3DMap[Shape3DEnum::SPHERE_3D][i]->Translate(velocity);
	}
}

//�Փ˔���
bool Actor3D::IsCollide(const Actor3D& other,HitInfo& info)const
{
	return false;
}