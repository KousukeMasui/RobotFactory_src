#ifndef	 _RESOURCE_H_
#define	 _RESOURCE_H_

enum class Font_ID
{
	SNAP_ITC=0,
	JAPANISE_FONT,//日本語用フォント
	MAX,
};


enum class EffectID
{
	HEAL = 0,
	POWER_UP,
	MAX
};

enum class MODEL_ID
{
	SKYDOME=0,   //空モデル
	GROUND,	   //地面
	CIRCLE,//
	UNIT,
	BOX,
	FACTORY,
	CLAMP_FIELD,
	PARTS,
	MAX,
};

enum class TEXTURE_ID
{
	PARTS = 0,
	BLACK,
	UNIT,
	ATTACK_UP,
	AUTO,
	HP_UP,
	SPEED_UP,
	BACK,
	FACTORY,
	HEAL_POWER,
	HEAL_RANGE,
	COMMAND_GAUGE,
	COMMAND_FRAME,
	CLOSE,
	CREATE,
	NUMBER,
	//hpゲージ
	HP_GAUGE,
	HP_FRAME,
	//ユニットが資源を持った際のUI
	HAVE_PARTS,
	HAVE_UNIT,

	STATUS_BACK,//ゲーム画面のユニットステータスの背景
	//result
	RESULT_TEXT,
	TO_TITLE,
	RETRY,

	//title
	TITLE_LOGO,
	CLICK_TO_START,

	//初期化用
	NONE,

	//工場のhpが0になった際のテクスチャ
	FACTORY_DEAD,
	FACTORY_GET,
	FACTORY_LOST,

	MAX,
};

#endif