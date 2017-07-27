#include "RootAgent.h"
#include"Math/Converter.h"
RootAgent::RootAgent(Object& object):
	m_object(object),
	m_isFindWait(false),
	m_rootModel(MODEL_ID::ROOT)
{
}

RootAgent::~RootAgent()
{
}

void RootAgent::Update(float deltaTime, float range)
{
	MyVector3 velocity;
	do {
		//経路がない場合false
		if (m_root.empty())
		{
			m_toNextVelocity = MyVector3::Zero();
			return;
		}
		//移動方向を求める
		velocity = m_root.back() - m_object.Position();

		//距離が一定以下の場合、再度計算させる
		if (velocity.Length() <= range)
		{
			m_root.pop_back();
		}
		else break;
	} while (true);

	//移動方向を変数に入れる
	m_toNextVelocity = velocity.Normalize();
}

MyVector3 RootAgent::ToNextVelocity() const
{
	return m_toNextVelocity;
}

bool RootAgent::RotateToNext(float deltaTime)
{
	return m_object.SlerpRotate(ToNextVelocity(), deltaTime);
}

bool RootAgent::IsFindWait() const
{
	return m_isFindWait;
}

void RootAgent::StartFind()
{
	m_isFindWait = true;
}

void RootAgent::SetRoot(const MyVector3 & position)
{
	m_root.clear();
	m_root.push_back(position);
}

void RootAgent::SetRoot(const std::vector<MyVector3>& root)
{
	m_root = root;
	m_isFindWait = false;
}

MyVector3 * RootAgent::Position()
{
	return m_object.PositionPtr();
}

bool RootAgent::IsMove() const
{
	return !m_root.empty();
}

const MyVector3 RootAgent::EndPoint() const
{
	if (m_root.empty()) return MyVector3::Zero();
	return m_root.front();
}

void RootAgent::Delete()
{
	m_root.clear();
}

void RootAgent::Draw(const Color& color) const
{
	m_rootModel.SetMaterialColor(0, color);
	MyVector3 prev = m_object.Position();
	for (auto itr = m_root.rbegin(); itr != m_root.rend(); itr++)
	{
		MyVector3 toPosition = *itr - prev;
		float zScale = MyVector3::Distance(prev, *itr);
		float rad = MyVector3::Angle(toPosition, MyVector3(0, 0, -1));
		if (Converter::RadToDeg(MyVector3::Angle(toPosition, MyVector3(1, 0, 0))) < 90.0f) {
			rad = -rad;
		}
		m_rootModel.Draw(prev + toPosition / 2 + MyVector3(0.0f, 2.0f, 0.0f), MyVector3(1, 10, zScale),
			MyMatrix4::RotateY(rad));
		prev = *itr;
	}
}
