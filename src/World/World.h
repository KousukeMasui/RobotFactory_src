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

//カメラの変更を行うための列挙
enum class CameraMode
{
	NORMAL = 0,//通常時
	DEBUG,//デバッグ用
	UNIT,//ユニット追従
};



//ワールドクラス
class World :public IWorld
{
public:
	//コンストラクタ
	World();
	//更新
	void Update(float deltaTime);
	//描画
	void Draw() const;

	//ステージ生成
	void StageCreate();
	//ゲームスタート
	void GameStart();
	//ゲーム終了
	void GameEnd();
	//ゲームリセット
	void GameReset();
	//カメラの追加
	void AddCamera(CameraMode mode,const std::shared_ptr<Camera>& camera) override;
	void SetCamera(CameraMode mode);
	virtual std::shared_ptr<Camera> GetCamera() const override;

	//ライトの追加
	void AddLight(const ActorPtr& light);


	virtual std::shared_ptr<Field> GetField() const override;

	//メッセージの送信
	virtual void MessageSend(EventMessage message, void* param = nullptr) override;

	//メッセージ処理
	void HandleMessage(EventMessage message, void* param = nullptr);

	//アクターの追加
	virtual void AddActor(ActorGroup group, const ActorPtr& actor) override;

	//アクターの検索
	virtual ActorPtr FindActor(const std::string& name)override;
	virtual std::vector<ActorPtr> FindActors(const ActorGroup& group) override;

	virtual  UIManager& GetUIManager() override;

	virtual GameManager& GetGameManager() override;

	virtual FieldMap& GetFieldMap() override;
	//コピー禁止
	World(const World& other) = delete;
	World& operator=(const World& other) = delete;

	//デバッグモードのための設定
	void DebugSet(Enemy* enemy);

	virtual std::shared_ptr<Effect3D> CreateEffect(EffectID effect) override;

	virtual BillBoardManager& GetBillBoardManager() override;

	void Command(const FactoryPtr& factory = nullptr) override;
	bool IsCommand() const;
	FactoryPtr GetCommandFactory() const override;
	MetaAI& GetMetaAI() override;
private:
	//ゲームの状態のステートパターン
	StateManager m_gameStateManager;
	//アクターマネージャー
	ActorManager m_actors;
	//スプライトマネージャー
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
	//ビルボードマネージャー
	BillBoardManager m_billBoardManager;
	FactoryPtr m_commandFactory;
	//メタAI
	MetaAI m_metaAI;
	//デバッグ
	std::shared_ptr<Debug> m_debug;
	//ワールド座標用スプライトクラス
	WorldToSpriteManager m_worldSpriteManager;
};

#endif