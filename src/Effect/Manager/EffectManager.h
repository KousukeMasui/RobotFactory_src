#pragma once
#include<forward_list>
#include<memory>
#include<map>
#include"../EffectPtr.h"
#include"Resources.h"
#include"Math/Vector/MyVector3.h"
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
	std::shared_ptr<Effect3D> CreateEffect(EffectID effect,const MyVector3& position,const MyVector3& scale =MyVector3(1,1,1));

	//削除関数
	void Remove();

private:
	//エフェクト格納変数
	std::forward_list<EffectPtr> m_effects;
};