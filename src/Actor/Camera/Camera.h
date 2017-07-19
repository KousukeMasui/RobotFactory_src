#ifndef	  _CAMERA_H_
#define	  _CAMERA_H_
#include"Object\Object.h"
class Camera:public Object
{
public:
	explicit Camera();
	explicit Camera(const MyVector3& rad);

	virtual void Update(float deltaTime);
	void Draw()const;

	//����\���̐ݒ�
	void Controll(bool isControll);
private:
	//�J�����̈ړ�����
	void CameraMove(const MyVector2& mouseVelocity,float deltaTime);
protected:
	//�J�����̉�]����
	void CameraRotate(const MyVector2& mouseVelocity);
	//�J�����̍s���ݒ肷��
	void CameraSet();
private:
	MyVector3 m_rad;//��]�p�x
	//���삷�邩
	bool m_isControll;
protected:
	//��]�Ȃ��̏ꍇ��target����̕���
	const MyVector3 m_defaultVelocity = MyVector3(0, 1, 0);

	//�����_
	MyVector3 m_target;
	//����
	float m_distance;
};

#endif