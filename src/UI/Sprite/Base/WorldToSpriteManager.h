#pragma once
#include"Resources.h"
#include<map>
#include<vector>
#include"Math/Vector/MyVector3.h"
#include"Math/Vector/MyVector2.h"
#include"Math/Color/Color.h"
#include"Math/MyRect/MyRect.h"
#include"UI/Sprite/Base/SpritePtr.h"
//���[���h���W����X�N���[�����W�ɕϊ����ĉ摜�`����s���N���X
class WorldToSpriteManager {
private:
	//�`��ɕK�v�ȃX�e�[�^�X
	struct SpriteParam {
		SpriteParam(TEXTURE_ID id,const MyVector2& position, const MyVector2& scale, float z, MyRect rect, Color color);
		TEXTURE_ID id;
		MyVector2 position;
		MyVector2 scale;
		float z;//�X�N���[�����W�ɂ����ۂ̃J�����Ƃ̋���(+-����)
		MyRect rect;
		Color color;
	};
public:
	WorldToSpriteManager();
	~WorldToSpriteManager();
	//�������֐� Sprite�𕡐���������̂�h�~���邽�߂ɍ쐬
	void Set(TEXTURE_ID id);

	//�ʒu��ۑ����� �摜�̏d�Ȃ��h�~���邽�߂Ɉ�x�ϐ��Ɋi�[���Ďg�p����
	void Save(TEXTURE_ID id, const MyVector3& position, const MyVector2& size);
	//rect�o�^�ňʒu�ۑ�
	void Save(TEXTURE_ID id, const MyVector3& position, const MyVector2& size,const MyRect& rect,const Color& color = Color::White);

	//�`��
	void Draw() const;
	//������
	void Clear();
private:
	//�`��\�Ȉʒu�ɂ��邩
	bool IsDraw(const MyVector3& position,MyVector3& screenPos);
private:
	std::vector<std::shared_ptr<SpriteParam>> m_spriteParams;
	std::map<TEXTURE_ID, SpritePtr> m_spriteMap;
};