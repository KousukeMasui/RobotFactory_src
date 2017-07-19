#include "Loader.h"

#include<DxLib.h>
#include"EffekseerForDXLib.h"
void Loader::Initialize()
{
	for (int i = 0; i < (int)TEXTURE_ID::MAX; i++)
	{
		m_textureHandle[(TEXTURE_ID)i] = -1;
	}
	for (int i = 0; i < (int)MODEL_ID::MAX; i++)
	{
		m_modelHandle[(MODEL_ID)i] = -1;
	}
	for (int i = 0; i < (int)Font_ID::MAX; i++)
	{
		m_fontHandle[(Font_ID)i] = -1;
	}
	for (int i = 0; i < (int)EffectID::MAX; i++)
	{
		m_effectHandle[(EffectID)i] = -1;
	}
}
void Loader::ModelLoad(MODEL_ID id, const char * fileName)
{
	if (m_modelHandle[id] != -1) return;
	m_modelHandle[id] = MV1LoadModel(fileName);
	//エラー時出力
	if (m_modelHandle[id] == -1)
	{
		printfDx(fileName);
		printfDx(" : 読み込み失敗\n");
	}
}

int Loader::ModelHandle(MODEL_ID id)
{
	return m_modelHandle[id];
}

int Loader::ModelCopy(MODEL_ID id)
{
	return MV1DuplicateModel(m_modelHandle[id]);
}

void Loader::ModelDelete(MODEL_ID id)
{
	MV1DeleteModel(m_modelHandle[id]);
}

void Loader::TextureLoad(TEXTURE_ID id, const char * fileName)
{
	if (m_textureHandle[id] != -1) return;
	m_textureHandle[id] = LoadGraph(fileName);
	//エラー時出力
	if (m_textureHandle[id] == -1)
	{
		printfDx(fileName);
		printfDx(" : 読み込み失敗\n");
	}
}

int Loader::TextureHandle(TEXTURE_ID id)
{
	return m_textureHandle.at(id);
}

void Loader::TextureDelete(TEXTURE_ID id)
{
	DeleteGraph(m_textureHandle[id]);
}
MyVector2 Loader::TextureSize(TEXTURE_ID id)
{
	int x, y;
	GetGraphSize(TextureHandle(id), &x, &y);
	return MyVector2((float)x, (float)y);
}
void Loader::FontLoad(Font_ID font, const char * fileName)
{
	if (m_fontHandle[font] != -1) return;
	m_fontHandle[font] = LoadFontDataToHandle(fileName);
}
int Loader::FontHandle(Font_ID font)
{
	return m_fontHandle[font];
}

void Loader::EffectLoad(EffectID effect, const char * fileName)
{
	m_effectHandle[effect] = LoadEffekseerEffect(fileName);
}

int Loader::EffectHandle(EffectID effect)
{
	return PlayEffekseer3DEffect(m_effectHandle.at(effect));
}
