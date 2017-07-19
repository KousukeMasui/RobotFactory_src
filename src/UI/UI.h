#pragma once

#include"Math/Vector/MyVector2.h"
#include"Math/Color/Color.h"
#include<vector>
#include<memory>
#include"Screen/Screen.h"
#include"UIAction/Base/UIActions.h"
class UI
{
public:
	UI(const MyVector2 & position, const Color & color);
	~UI();

	bool Update(float deltaTime);

	void SetAction(const std::shared_ptr<UIAction>& action);
	bool IsSetAction();

	virtual void Draw() const = 0;
	void Alpha(const float& alpha);
	float Alpha() const;

	void Position(const MyVector2& pos);
	MyVector2 Position() const;

	Color GetColor() const;
	void SetColor(const Color& color);

	void AddChild(const std::shared_ptr<UI>& child);

	bool IsDelete();
private:
	//�X�N���[���̉𑜓x���ς�����ۂɃ��C�A�E�g���ς��Ȃ��悤�ɕ␳����֐�
	MyVector2 SetScreenSizePosition(const MyVector2 & pos) const;
protected:
	MyVector2 m_position;
	MyVector2 m_drawPos;
	Color m_color;
	std::vector<std::shared_ptr<UI>> m_children;
	//�A�N�V����
	std::shared_ptr<UIAction> m_action;
	//���񂾂�
	bool m_isDead;
};