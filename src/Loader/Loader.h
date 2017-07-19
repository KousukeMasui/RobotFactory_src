#pragma once

#include<map>
#include"Resources.h"
#include"Math/Vector/MyVector2.h"
//���\�[�X�����[�h����N���X
class Loader
{
private:
	Loader() = default;
	~Loader() = default;

public:
	//�R�s�[�֎~
	Loader(const Loader&) = delete;
	Loader& operator=(const Loader&) = delete;
	Loader(Loader&&) = delete;
	Loader& operator=(Loader&&) = delete;

	static Loader& GetInstance()
	{
		static Loader inst;
		return inst;
	}
	//������
	void Initialize();

	//���f���̃��[�h
	void ModelLoad(MODEL_ID id, const char* fileName);
	//���f���n���h����Ԃ�
	int ModelHandle(MODEL_ID id);
	//���f���̃R�s�[��Ԃ�
	int ModelCopy(MODEL_ID id);
	//���f�����폜����
	void ModelDelete(MODEL_ID id);

	//�e�N�X�`���̃��[�h
	void TextureLoad(TEXTURE_ID id, const char* fileName);
	int TextureHandle(TEXTURE_ID id);
	void TextureDelete(TEXTURE_ID id);
	MyVector2 TextureSize(TEXTURE_ID id);

	//�t�H���g�̃��[�h
	void FontLoad(Font_ID font, const char* fileName);
	int FontHandle(Font_ID font);
	void EffectLoad(EffectID effect, const char* fileName);
	int EffectHandle(EffectID effect);

private:
	std::map<MODEL_ID, int> m_modelHandle;
	std::map<TEXTURE_ID, int> m_textureHandle;
	std::map<Font_ID, int> m_fontHandle;
	std::map<EffectID, int> m_effectHandle;
};