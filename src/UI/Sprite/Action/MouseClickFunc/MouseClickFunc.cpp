#include "MouseClickFunc.h"
#include"Input\Mouse\Mouse.h"
#include"../../Sprite.h"
MouseClickFunc::MouseClickFunc(const std::function<void(Sprite* sprite)>& clickFunc):
	m_clickFunc(clickFunc),
	m_nonClickFunc([](Sprite* sprite) {})
{
}

MouseClickFunc::MouseClickFunc(const std::function<void(Sprite* sprite)>& clickFunc, const std::function<void(Sprite* sprite)>& nonClickFunc):
	m_clickFunc(clickFunc),
	m_nonClickFunc(nonClickFunc)
{
}

MouseClickFunc::~MouseClickFunc()
{
}

bool MouseClickFunc::OnUpdate(Sprite* sprite, float deltaTime)
{
	//�����蔻��ׂ̈ɍ���ƉE�����擾
	MyVector2 leftUp = sprite->Position();
	MyVector2 rightDown = sprite->Position() + MyVector2(sprite->TexSize().x * sprite->Scale().x, sprite->TexSize().y * sprite->Scale().y);
	//�}�E�X�̈ʒu���e�N�X�`���̏�̏ꍇ
	if (MyVector2::Inside(Mouse::GetInstance().Position(), leftUp, rightDown))
	{
		if (m_clickFunc == nullptr) return false;
		//function���s
		m_clickFunc(sprite);
	}
	else
	{
		if (m_nonClickFunc == nullptr) return false;
		m_nonClickFunc(sprite);
	}
	return false;
}
