#pragma once
#include"UI/UI.h"
#include"Math/MyRect/MyRect.h"
#include"Resources.h"
//2D�e�N�X�`���`��N���X
class Sprite: public UI
{
public:
	//�f�t�H���g�R���X�g���N�^
	Sprite();
	//�R���X�g���N�^
	Sprite(TEXTURE_ID id,MyVector2 position,MyVector2 scale,MyVector2 center);
	//�f�X�g���N�^
	~Sprite();
	//�`��
	void Draw() const override;
	//�g�嗦
	void Scale(const MyVector2& scale);
	MyVector2 Scale() const;
	//��]�̒��S�ʒu
	void Center(const MyVector2& center);
	MyVector2 Center() const;
	//�摜�̐؂���ʒu
	void Rect(const MyRect& rect);
	MyRect Rect() const;
	//��]�p�x
	void Rad(const float& rad);
	float Rad() const;
	//�e�N�X�`���̑傫��
	MyVector2 TexSize() const;
	//�e�N�X�`����ID
	TEXTURE_ID TexID() const;
	//�����蔻��
	bool IsCollide(const MyVector2& position) const;
private:
	//�𑜓x���ύX����Ă��`�惌�C�A�E�g��ύX���Ȃ����߂̊֐�
	MyVector2 SetScreenSizeScale(const MyVector2 & scale) const;
private:
	TEXTURE_ID m_texID;
protected:
	MyVector2 m_scale;
	MyVector2 m_center;
	MyRect m_rect;
	float m_rad;
	//�X�P�[���������Ȃ��{���̑傫��
	MyVector2 m_texSize;

	MyVector2 m_drawScale;

};