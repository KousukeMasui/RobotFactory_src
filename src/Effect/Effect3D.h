#pragma once
#include"Math/Vector/MyVector3.h"
#include<functional>
//Effekseer�̃G�t�F�N�g�����b�s���O����N���X
class Effect3D//Effect���Ɩ��O��������VC�̓��������肵�Ȃ��̂Ŗ��O��ύX
{
public:
	explicit Effect3D(int playHandle);
	~Effect3D();
	
	void Update(float deltaTime);//�X�V����
	void Stop(bool isStop);

	void Draw() const;
	void Delete();//�폜�֐�
	bool IsDelete() const;//�폜���邩

	//�Đ������擾
	bool IsPlay() const;

	void SetPosition(const MyVector3& position);
	void SetScale(const MyVector3& scale);
	void SetPositionFunc(const std::function<MyVector3()>& func);
private:

	int m_playHandle;//�Đ�����ۂ̃n���h��

	bool m_isDelete;//�폜���鎞true

	bool m_isStop;

	//�ʒu�Ǐ]�p�ϐ�
	std::function<MyVector3()> m_positionFunc;
};