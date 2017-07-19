#ifndef	 _RESOURCE_H_
#define	 _RESOURCE_H_

enum class Font_ID
{
	SNAP_ITC=0,
	JAPANISE_FONT,//���{��p�t�H���g
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
	SKYDOME=0,   //�󃂃f��
	GROUND,	   //�n��
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
	//hp�Q�[�W
	HP_GAUGE,
	HP_FRAME,
	//���j�b�g���������������ۂ�UI
	HAVE_PARTS,
	HAVE_UNIT,

	STATUS_BACK,//�Q�[����ʂ̃��j�b�g�X�e�[�^�X�̔w�i
	//result
	RESULT_TEXT,
	TO_TITLE,
	RETRY,

	//title
	TITLE_LOGO,
	CLICK_TO_START,

	//�������p
	NONE,

	//�H���hp��0�ɂȂ����ۂ̃e�N�X�`��
	FACTORY_DEAD,
	FACTORY_GET,
	FACTORY_LOST,

	MAX,
};

#endif