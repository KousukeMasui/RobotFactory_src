#ifndef	 _LIGHT_H_
#define	 _LIGHT_H_

#include"../Base/Actor3D.h"

//ライトクラス
class Light :public Actor3D
{
public:
	//コンストラクタ
	Light(IWorld& world, const MyVector3& position);

	void OnUpdate(float deltaTime) override;

	void OnDraw()const override;
	
protected://今後他2種類のライトを設定するので。
	MyVector3 m_direction;//ライトの向き
	COLOR_F m_ambient;//ambientカラー
	COLOR_F m_diffuse;//diffuseカラー
	COLOR_F m_specular;//specularカラー


};


#endif