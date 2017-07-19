#pragma once
#include<forward_list>
#include<memory>
#include<map>
#include"../EffectPtr.h"
#include"Resources.h"
//Effekseerのエフェクトの管理クラス
class EffectManager
{
public:
	//コンストラクタ
	EffectManager();
	//デストラクタ
	~EffectManager();

	void Update(float deltaTime);//更新
	void Draw() const;//描画

	//生成関数
	std::shared_ptr<Effect3D> CreateEffect(EffectID effect);

	//削除関数
	void Remove();

private:
	//エフェクト格納変数
	std::forward_list<EffectPtr> m_effects;
};