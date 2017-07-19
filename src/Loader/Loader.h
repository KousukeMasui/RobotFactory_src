#pragma once

#include<map>
#include"Resources.h"
#include"Math/Vector/MyVector2.h"
//リソースをロードするクラス
class Loader
{
private:
	Loader() = default;
	~Loader() = default;

public:
	//コピー禁止
	Loader(const Loader&) = delete;
	Loader& operator=(const Loader&) = delete;
	Loader(Loader&&) = delete;
	Loader& operator=(Loader&&) = delete;

	static Loader& GetInstance()
	{
		static Loader inst;
		return inst;
	}
	//初期化
	void Initialize();

	//モデルのロード
	void ModelLoad(MODEL_ID id, const char* fileName);
	//モデルハンドルを返す
	int ModelHandle(MODEL_ID id);
	//モデルのコピーを返す
	int ModelCopy(MODEL_ID id);
	//モデルを削除する
	void ModelDelete(MODEL_ID id);

	//テクスチャのロード
	void TextureLoad(TEXTURE_ID id, const char* fileName);
	int TextureHandle(TEXTURE_ID id);
	void TextureDelete(TEXTURE_ID id);
	MyVector2 TextureSize(TEXTURE_ID id);

	//フォントのロード
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