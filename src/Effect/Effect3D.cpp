#include "Effect3D.h"
#include"EffekseerForDXLib.h"
Effect3D::Effect3D(int playHandle):
	m_playHandle(playHandle),
	m_isDelete(false),
	m_isStop(false),
	m_positionFunc(nullptr)
{
}

Effect3D::~Effect3D()
{
	//DeleteEffekseerEffect(m_playHandle);
}

void Effect3D::Update(float deltaTime)
{
	if (m_isStop) return;
	if (m_positionFunc != nullptr)
		SetPosition(m_positionFunc());
	GetEffekseer3DManager()->UpdateHandle(m_playHandle, deltaTime);
	//Ä¶‚ªI‚í‚Á‚½ê‡Aíœ
	if (IsEffekseer3DEffectPlaying(m_playHandle) == -1)
		Delete();
}

void Effect3D::Stop(bool isStop)
{
	m_isStop = isStop;
}

void Effect3D::Draw() const
{
	GetEffekseer3DManager()->DrawHandle(m_playHandle);
	//DrawEffekseer3D();//‘S‚Ä‚ð•`‰æ
}

void Effect3D::Delete()
{
	m_isDelete = true;
	GetEffekseer3DManager()->StopEffect(m_playHandle);
}

bool Effect3D::IsDelete() const
{
	return m_isDelete;
}

bool Effect3D::IsPlay() const
{
	return IsEffekseer3DEffectPlaying(m_playHandle) == 0;
}

void Effect3D::SetPosition(const MyVector3 & position)
{
	SetPosPlayingEffekseer3DEffect(m_playHandle, position.x, position.y, position.z);
}

void Effect3D::SetScale(const MyVector3 & scale)
{
	SetScalePlayingEffekseer3DEffect(m_playHandle, scale.x, scale.y, scale.z);
}

void Effect3D::SetPositionFunc(const std::function<MyVector3()>& func)
{
	m_positionFunc = func;
}
