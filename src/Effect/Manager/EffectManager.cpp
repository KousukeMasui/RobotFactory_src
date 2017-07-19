#include "EffectManager.h"

#include"EffekseerForDXLib.h"
#include"Effect/Effect3D.h"
#include"Loader\Loader.h"
#include"Input/Mouse/Mouse.h"
EffectManager::EffectManager()
{
}

EffectManager::~EffectManager()
{
}

void EffectManager::Update(float deltaTime)
{
	//�G�t�F�N�g�P�ʂ̍X�V
	GetEffekseer3DManager()->BeginUpdate();
	for (auto effect : m_effects)
	{
		effect->Update(deltaTime);//�X�V����
	}
	GetEffekseer3DManager()->EndUpdate();

	Remove();
}

void EffectManager::Draw() const
{
	DrawEffekseer3D();//�S�Ă�`��
	//GetEffekseer3DRenderer()->BeginRendering();
	//for (auto effect : m_effects)
	//{
	//	effect->Draw();//�`�揈��
	//}
	//GetEffekseer3DRenderer()->EndRendering();
}

std::shared_ptr<Effect3D> EffectManager::CreateEffect(EffectID effect)
{
	auto e = std::make_shared<Effect3D>(Loader::GetInstance().EffectHandle(effect));
	
	m_effects.push_front(e);

	return e;
}

void EffectManager::Remove()
{
	m_effects.remove_if(
		[](std::shared_ptr<Effect3D> type)
	{
		return type->IsDelete();
	});
}
