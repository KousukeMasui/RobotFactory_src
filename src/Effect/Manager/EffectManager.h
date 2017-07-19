#pragma once
#include<forward_list>
#include<memory>
#include<map>
#include"../EffectPtr.h"
#include"Resources.h"
//Effekseer�̃G�t�F�N�g�̊Ǘ��N���X
class EffectManager
{
public:
	//�R���X�g���N�^
	EffectManager();
	//�f�X�g���N�^
	~EffectManager();

	void Update(float deltaTime);//�X�V
	void Draw() const;//�`��

	//�����֐�
	std::shared_ptr<Effect3D> CreateEffect(EffectID effect);

	//�폜�֐�
	void Remove();

private:
	//�G�t�F�N�g�i�[�ϐ�
	std::forward_list<EffectPtr> m_effects;
};