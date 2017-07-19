#pragma once
#include"UI/UIAction/Base/UIActions.h"
#include"../../FontSprite.h"
#include<string>
//fontSprite�̕�������ꕶ�����`�悷��N���X
class AddTextAction : public FontAction {
public:
	//�R���X�g���N�^
	AddTextAction(const char* startText,const char* addText,float addTime,bool isLoop);
	//�f�X�g���N�^
	~AddTextAction();
	//�X�V
	bool OnUpdate(FontSprite* font, float deltaTime) override;

private:
	//�����e�L�X�g
	const char* m_startText;
	//�`�悵�Ă���������
	const char* m_addText;
	//�`��X�V����܂ł̎���
	const float m_addTime;
	//�`��X�V�^�C�}
	float m_addTimer;

	//���݉������ڂ܂ŕ`�悵����
	int m_drawIndex;
	//���[�v���邩
	bool m_isLoop;
};