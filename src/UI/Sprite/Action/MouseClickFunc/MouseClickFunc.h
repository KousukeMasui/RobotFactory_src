#pragma once
#include"UI/UIAction/Base/UIActions.h"
#include"../../Sprite.h"
#include<functional>
//�}�E�X�ŃN���b�N�����ۂ̏������s���֐�
class MouseClickFunc : public SpriteAction
{
public:
	explicit MouseClickFunc(const std::function<void(Sprite* sprite)>& clickFunc);
	MouseClickFunc(const std::function<void(Sprite* sprite)>& clickFunc,
		const std::function<void(Sprite* sprite)>& nonClickFunc);
	~MouseClickFunc();

	virtual bool OnUpdate(Sprite* sprite, float deltaTime) override;

private:
	std::function<void(Sprite* sprite)> m_clickFunc;
	std::function<void(Sprite* sprite)> m_nonClickFunc;
};