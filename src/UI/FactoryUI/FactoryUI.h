#pragma once
#include"UI/UIManager/UIManager.h"
#include"Base/GameUsing.h"
#include"Actor\Base\IWorld.h"
#include"Actor\UnitFactory\Status\FactoryStatus.h"
#include"UI/UIAction/SameTime/SameTime.h"
#include"Scene/GamePlay/GamePlaySpriteID.h"
class Player;
//�H��UI���쐬����N���X
enum DrawCommand
{
	COMMAND_FIRST,
	COMMAND_STATUS,
	COMMAND_HEAL,
	COMMAND_AUTO
};
class FactoryUI
{
public:
	explicit FactoryUI(IWorld& world);
	~FactoryUI();
	void Update(float deltaTime);
	void Create(const FactoryPtr& factory);
	void Delete(GamePlaySpriteID createID);

	void Delete();
	void Draw() const;

	bool IsAuto() const;
private:
	void StatusGaugeDraw() const;
	void HealGaugeDraw() const;
	//�Q�[�W�\��
	void GaugeDraw(MyVector2 startPosition, MyVector2 texSize,int size) const;
	void Initialize();
	//�J�����ۂ̃R�}���hUI���쐬����
	void FirstCommand();
	//���j�b�g�X�e�[�^�XUI���쐬
	void StatusCommand();
	//��UI���쐬
	void HealCommand();
	//�X�e�[�^�X�R�}���h�̃A�N�V������Ԃ�
	std::shared_ptr<SameTime> CreateStatusAction();
private:
	IWorld& m_world;
	UIManager m_manager;
	//�N���b�N�Œǉ����̃X�v���C�g���ꎞ�ϐ����Ɣj������Ă��܂��̂ł����j�~����ϐ�
	std::map<int,SpritePtr> m_sprites;
	//�ǂ̃X�e�[�^�X���グ�邩���i�[
	std::map<TEXTURE_ID, FactoryStatusID> m_status;
	//���̃R�}���h���󂯕t����H��
	FactoryPtr m_factory;
	//�v���C���[
	std::shared_ptr<Player> m_player;
	DrawCommand m_command;
};