#include"Light.h"

//コンストラクタ
Light::Light(IWorld& world, const MyVector3& position) :
Actor3D(world, "Light", position)
{
}

void Light::OnUpdate(float deltaTime)
{
	(void)deltaTime;
}

void Light::OnDraw()const
{
	//ライトの色が良く分からない場合は
		//http://www.geocities.jp/neo_ku_ron/HP_NEW/GameProgram/LightCharacter/LightCharacter.html
	//を参照すること
	//diffuse
	SetLightDifColor(GetColorF(1.0f, 1.0f, 1.0f, 1.0f));
	//ambient
	SetLightAmbColor(GetColorF(1.0f, 1.0f, 1.0f, 1.0f));
	//speclar
	SetLightSpcColor(GetColorF(1.0f, 1.0f, 1.0f, 1.0f));
	//position
	SetLightPosition(Converter::MyVector3ToVECTOR(m_position));
	//向き ステージの中心に向ける
	SetLightDirection(Converter::MyVector3ToVECTOR(MyVector3(800,0,800) - m_position));

	//SetLightRangeAtten();
}