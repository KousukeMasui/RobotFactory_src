#include "UI.h"

UI::UI(const MyVector2 & position, const Color & color) :
	m_position(position),
	m_drawPos(SetScreenSizePosition(position)),
	m_color(color),
	m_action(nullptr),
	m_isDead(false)
{
}

UI::~UI()
{
}

bool UI::Update(float deltaTime)
{
	for (auto child : m_children)
		child->Update(deltaTime);
	if (m_action == nullptr) return true;
	auto isEnd = m_action->Update(this, deltaTime);
	if (isEnd)
	{
		m_action = nullptr;
		return true;
	}
	return false;
}

void UI::SetAction(const std::shared_ptr<UIAction>& action) {
	m_action = action;
}

bool UI::IsSetAction()
{
	return m_action != nullptr;
}

void UI::Alpha(const float & alpha)
{
	this->m_color.a = alpha;
}

float UI::Alpha() const
{
	return m_color.a;
}

void UI::Position(const MyVector2 & pos)
{
	MyVector2 velocity = pos - m_position;
	//子も同じ分だけ移動させる
	for (auto child : m_children)
	{
		child->Position(child->Position() + velocity);
	}
	m_position = pos;
	m_drawPos = SetScreenSizePosition(pos);
}

MyVector2 UI::Position() const
{
	return m_position;
}

Color UI::GetColor() const {
	return m_color;
}

void UI::SetColor(const Color & color) {
	m_color = color;
}

void UI::AddChild(const std::shared_ptr<UI>& child) {
	m_children.push_back(child);
}

bool UI::IsDelete() {
	return m_isDead;
}

//スクリーンの解像度が変わった際にレイアウトが変わらないように補正する関数

MyVector2 UI::SetScreenSizePosition(const MyVector2 & pos) const {
	return MyVector2(pos.x * Screen::RESOLUTION.x / Screen::SCREEN_SIZE.x, pos.y*Screen::RESOLUTION.y / Screen::SCREEN_SIZE.y);
}
