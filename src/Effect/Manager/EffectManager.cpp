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
	//エフェクト単位の更新
	GetEffekseer3DManager()->BeginUpdate();
	for (auto effect : m_effects)
	{
		effect->Update(deltaTime);//更新処理
	}
	GetEffekseer3DManager()->EndUpdate();

	Remove();
}

void EffectManager::Draw() const
{
	DrawEffekseer3D();//全てを描画
	//GetEffekseer3DRenderer()->BeginRendering();
	//for (auto effect : m_effects)
	//{
	//	effect->Draw();//描画処理
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
