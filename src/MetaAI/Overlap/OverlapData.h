#pragma once
#include<forward_list>
//�d�������Ȃ����߂ɕϐ��ɕۑ����Ă���
class OverlapData
{
public:
	//�R���X�g���N�^
	OverlapData();
	//�f�X�g���N�^
	~OverlapData();

	//�ǉ�
	void Add(void* data);
	//�폜
	void Remove(void* data);
	//���Ɋi�[����Ă��邩����
	bool IsContains(void* data);
private:
	//�f�[�^
	std::forward_list<void*> m_data;
};