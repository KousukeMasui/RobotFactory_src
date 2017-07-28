#include "RootAgent.h"
#include"Math/Converter.h"
#include"RootFind.h"
RootAgent::RootAgent(RootFind& find,Object& object):
	m_find(find),
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
	m_toNextVelocity = MyVector3::Zero();
	MyVector3 velocity;
	do {
		//経路がない場合return
		if (m_root.empty()) return;
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

void RootAgent::StartFind(const MyVector3 & target, bool isPriority)
{
	m_isFindWait = true;
	m_find.PathFind(m_find.CreatePathFinder(), target, *this, isPriority);
}

void RootAgent::StartFind(const std::vector<Point2>& targets, const std::vector<Point2>& removes, bool isPriority)
{
	auto f = m_find.CreatePathFinder();
	for (auto p : removes)
		f[p]->SetWalkable(false);//移動不可として扱う
	m_isFindWait = true;
	m_find.PathFind(f, targets, *this, isPriority);
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
