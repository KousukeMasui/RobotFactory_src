#ifndef	 _WORLD_H_
#define	 _WORLD_H_

#include"../Actor/Base/IWorld.h"


#include "../Actor/Base/ActorManager.h"
#include"Actor/Influence/Player/Player.h"
#include"Actor/Influence/Enemy/Enemy.h"
#include"Manager\GameManager.h"
#include"Base\RoadFinder\Map\FieldMap.h"
#include"UI/FactoryUI/FactoryUI.h"
#include"Debug\Debug.h"
#include"UI/Sprite\BillBoard\Manager\BillBoardManager.h"
#include"Actor/Influence/AIAction/MetaAI/MetaAI.h"
#include"UI/Sprite/Base/WorldToSpriteManager.h"
class EffectManager;

//�J�����̕ύX���s�����߂̗�
enum class CameraMode
{
	NORMAL = 0,//�ʏ펞
	DEBUG,//�f�o�b�O�p
	UNIT,//���j�b�g�Ǐ]
};



//���[���h�N���X
class World :public IWorld
{
public:
	//�R���X�g���N�^
	World();
	//�X�V
	void Update(float deltaTime);
	//�`��
	void Draw() const;

	//�X�e�[�W����
	void StageCreate();
	//�Q�[���X�^�[�g
	void GameStart();
	//�Q�[���I��
	void GameEnd();
	//�Q�[�����Z�b�g
	void GameReset();
	//�J�����̒ǉ�
	void AddCamera(CameraMode mode,const std::shared_ptr<Camera>& camera) override;
	void SetCamera(CameraMode mode);
	virtual std::shared_ptr<Camera> GetCamera() const override;

	//���C�g�̒ǉ�
	void AddLight(const ActorPtr& light);


	virtual std::shared_ptr<Field> GetField() const override;

	//���b�Z�[�W�̑��M
	virtual void MessageSend(EventMessage message, void* param = nullptr) override;

	//���b�Z�[�W����
	void HandleMessage(EventMessage message, void* param = nullptr);

	//�A�N�^�[�̒ǉ�
	virtual void AddActor(ActorGroup group, const ActorPtr& actor) override;

	//�A�N�^�[�̌���
	virtual ActorPtr FindActor(const std::string& name)override;
	virtual std::vector<ActorPtr> FindActors(const ActorGroup& group) override;

	virtual  UIManager& GetUIManager() override;

	virtual GameManager& GetGameManager() override;

	virtual FieldMap& GetFieldMap() override;
	//�R�s�[�֎~
	World(const World& other) = delete;
	World& operator=(const World& other) = delete;

	//�f�o�b�O���[�h�̂��߂̐ݒ�
	void DebugSet(Enemy* enemy);

	virtual std::shared_ptr<Effect3D> CreateEffect(EffectID effect) override;

	virtual BillBoardManager& GetBillBoardManager() override;

	void Command(const FactoryPtr& factory = nullptr) override;
	bool IsCommand() const;
	FactoryPtr GetCommandFactory() const override;
	MetaAI& GetMetaAI() override;
private:
	//�Q�[���̏�Ԃ̃X�e�[�g�p�^�[��
	StateManager m_gameStateManager;
	//�A�N�^�[�}�l�[�W���[
	ActorManager m_actors;
	//�X�v���C�g�}�l�[�W���[
	UIManager m_UIManager;
	std::shared_ptr<GameManager> m_gameManager;
	CameraMode m_cameraMode;
	std::map<CameraMode,std::shared_ptr<Camera>> m_camera;
	ActorPtr m_light;
	std::shared_ptr<Field> m_field;

	bool m_isPouse;
	bool m_isUIDraw;
	FieldMap m_fieldMap;
	std::shared_ptr<EffectManager> m_effectManager;
	//�r���{�[�h�}�l�[�W���[
	BillBoardManager m_billBoardManager;
	FactoryPtr m_commandFactory;
	//���^AI
	MetaAI m_metaAI;
	//�f�o�b�O
	std::shared_ptr<Debug> m_debug;
	//���[���h���W�p�X�v���C�g�N���X
	WorldToSpriteManager m_worldSpriteManager;
};

#endif