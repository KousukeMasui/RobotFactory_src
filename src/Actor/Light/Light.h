#ifndef	 _LIGHT_H_
#define	 _LIGHT_H_

#include"../Base/Actor3D.h"

//���C�g�N���X
class Light :public Actor3D
{
public:
	//�R���X�g���N�^
	Light(IWorld& world, const MyVector3& position);

	void OnUpdate(float deltaTime) override;

	void OnDraw()const override;
	
protected://���㑼2��ނ̃��C�g��ݒ肷��̂ŁB
	MyVector3 m_direction;//���C�g�̌���
	COLOR_F m_ambient;//ambient�J���[
	COLOR_F m_diffuse;//diffuse�J���[
	COLOR_F m_specular;//specular�J���[


};


#endif