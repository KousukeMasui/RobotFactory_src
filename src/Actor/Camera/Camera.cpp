#include"Camera.h"
#include"../Base/IWorld.h"
#include"Math/Converter.h"
#include"Math/Matrix/MyMatrix4.h"
#include<math.h>
#include"Input/Mouse/Mouse.h"

#include"Manager\GameManager.h"
#include"Math/MyMath.h"
#include"EffekseerForDXLib.h"

Camera::Camera():
	Object(MyVector3(),MyMatrix4::Identity()),
	m_target(400.0f, 0.0f, 792.0f),
	m_distance(300.0f),
	m_rad(Converter::DegToRad(-60.0f), Converter::DegToRad(90.0f), 0.0f),
	m_isControll(false)
{
	m_rotate = MyMatrix4::RotateZXY(m_rad);
	CameraSet();
}

Camera::Camera( const MyVector3 & rad):
	Object(MyVector3(), MyMatrix4::RotateZXY(rad)),
	m_distance(300.0f),
	m_rad(rad),
	m_isControll(false)
{
	CameraSet();
}

void Camera::Update(float deltaTime)
{
	if (!m_isControll) return;
	MyVector2 mouseVelocity = Mouse::GetInstance().Velocity() / 10.0f;

	//マウスの移動に応じて移動させる
	CameraMove(mouseVelocity,deltaTime);
	//マウスの移動に応じて回転させる
	CameraRotate(mouseVelocity);

	//カメラの行列を設定
	CameraSet();

}
void Camera::Draw()const
{
	SetUseZBuffer3D(true);//基本図形用Zバッファを有効に 後でコメントアウト
}

void Camera::Controll(bool isControll)
{
	m_isControll = isControll;
}

void Camera::CameraMove(const MyVector2& mouseVelocity, float deltaTime)
{
	//移動処理
	if (Mouse::GetInstance().IsPressState(MouseCommand::MIDDLE))
	{
		MyVector3 velocity =
			m_rotate.GetForward() * -mouseVelocity.y +
			m_rotate.GetLeft() * mouseVelocity.x;

		m_target += velocity * m_distance / 200.0f * deltaTime;
		m_target.y = 0.0f;
	}

}
void Camera::CameraRotate(const MyVector2 & mouseVelocity)
{
	//回転処理
	if (Mouse::GetInstance().IsPressState(MouseCommand::RIGHT))
	{
		MyMatrix4 rot = MyMatrix4::RotateX(Converter::DegToRad(mouseVelocity.x)) * MyMatrix4::RotateX(mouseVelocity.y / 10.0f);
		m_rad.x = Converter::DegToRad(MyMath::Clamp(Converter::RadToDeg(m_rad.x) + mouseVelocity.y, -80.0f, 0.0f));
		m_rad.y += Converter::DegToRad(mouseVelocity.x);
		m_rotate = MyMatrix4::RotateZXY(m_rad);
	}
}

void Camera::CameraSet()
{
	//カメラがtargetに近づきすぎないように補正
	m_distance = std::fmaxf(m_distance - Mouse::GetInstance().Wheel()*5.0f, 100.0f);
	//targetから位置を求める
	m_position = m_target + (m_defaultVelocity * m_rotate).Normalize() * m_distance;
	//Nearはできる限り大きくしないとモデルにジャギが発生する
	SetCameraNearFar(10.0f, 100000.0f);
	SetupCamera_Perspective(45.0f);//60.0fの2択

	SetCameraPositionAndTargetAndUpVec(
		Converter::MyVector3ToVECTOR(m_position),
		Converter::MyVector3ToVECTOR(m_target),
		Converter::MyVector3ToVECTOR(m_rotate.GetForward()));

	Effekseer_Sync3DSetting();//Effekseerの3D用設定
}
