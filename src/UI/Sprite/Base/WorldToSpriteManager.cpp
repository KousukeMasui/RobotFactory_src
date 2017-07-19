#include "WorldToSpriteManager.h"
#include"../Sprite.h"
#include<DxLib.h>
#include"Math/Converter.h"
#include"Base/VectorUtility/VectorUtility.h"
WorldToSpriteManager::WorldToSpriteManager()
{
}

WorldToSpriteManager::~WorldToSpriteManager()
{
}

void WorldToSpriteManager::Set(TEXTURE_ID id)
{
	m_spriteMap[id] = std::make_shared<Sprite>(id, MyVector2(), MyVector2(1.0f, 1.0f), MyVector2());
}

void WorldToSpriteManager::Save(TEXTURE_ID id, const MyVector3 & position, const MyVector2 & size)
{
	Save(id, position, size,MyRect(0,0, m_spriteMap[id]->TexSize().x, m_spriteMap[id]->TexSize().y));
}

void WorldToSpriteManager::Save(TEXTURE_ID id, const MyVector3 & position, const MyVector2 & size, const MyRect & rect, const Color& color)
{
	MyVector3 screenPos;
	if (!IsDraw(position, screenPos)) return;//�X�N���[�����ɑ��݂��邩�`�F�b�N

	MyVector2 s = size *std::abs(1 - screenPos.z);
	m_spriteMap[id]->Scale(s);
	screenPos -= (MyVector3(m_spriteMap[id]->TexSize().x*m_spriteMap[id]->Scale().x, m_spriteMap[id]->TexSize().y*m_spriteMap[id]->Scale().y, 0) / 2);
	MyVector2 pos(screenPos.x, screenPos.y);
	m_spriteParams.push_back(std::make_shared<SpriteParam>(id,pos, s, screenPos.z,rect,color));
}
//�`��֐�
void WorldToSpriteManager::Draw() const
{
	//�������قǃJ�����ɋ߂��̂ŁA�傫�����Ƀ\�[�g
	auto params = VectorUtility::SortObject<std::shared_ptr<SpriteParam>>(m_spriteParams, [](const std::shared_ptr<SpriteParam>& p1, const std::shared_ptr<SpriteParam>& p2) {
		if (p1->z >= p2->z) return p1;
		return p2;
	});

	for (auto param : params)
	{
		//�p�����[�^�̐ݒ�
		m_spriteMap.at(param->id)->Scale(param->scale);
		m_spriteMap.at(param->id)->Position(param->position);
		m_spriteMap.at(param->id)->Rect(param->rect);
		m_spriteMap.at(param->id)->SetColor(param->color);
		//�`��
		m_spriteMap.at(param->id)->Draw();
	}
}

void WorldToSpriteManager::Clear()
{
	//�X�v���C�g�p�����[�^�̏���
	m_spriteParams.clear();
}

//�`��\�Ȉʒu�ɂ��邩
bool WorldToSpriteManager::IsDraw(const MyVector3 & position, MyVector3 & screenPos)
{
	screenPos = Converter::VECTORToMyVector3(ConvWorldPosToScreenPos(Converter::MyVector3ToVECTOR(position)));
	return !(screenPos.z < 0.0f || screenPos.z > 1.0f);
}

WorldToSpriteManager::SpriteParam::SpriteParam(TEXTURE_ID id,const MyVector2 & position, const MyVector2 & scale, float z, MyRect rect
	, Color color):
	id(id),
	position(position),
	scale(scale),
	z(z),
	rect(rect),
	color(color)
{
}
