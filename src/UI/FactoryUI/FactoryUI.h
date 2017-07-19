#pragma once
#include"UI/UIManager/UIManager.h"
#include"Base/GameUsing.h"
#include"Actor\Base\IWorld.h"
#include"Actor\UnitFactory\Status\FactoryStatus.h"
#include"UI/UIAction/SameTime/SameTime.h"
#include"Scene/GamePlay/GamePlaySpriteID.h"
class Player;
//工場UIを作成するクラス
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
	//ゲージ表示
	void GaugeDraw(MyVector2 startPosition, MyVector2 texSize,int size) const;
	void Initialize();
	//開いた際のコマンドUIを作成する
	void FirstCommand();
	//ユニットステータスUIを作成
	void StatusCommand();
	//回復UIを作成
	void HealCommand();
	//ステータスコマンドのアクションを返す
	std::shared_ptr<SameTime> CreateStatusAction();
private:
	IWorld& m_world;
	UIManager m_manager;
	//クリックで追加等のスプライトが一時変数だと破棄されてしまうのでそれを阻止する変数
	std::map<int,SpritePtr> m_sprites;
	//どのステータスを上げるかを格納
	std::map<TEXTURE_ID, FactoryStatusID> m_status;
	//このコマンドを受け付ける工場
	FactoryPtr m_factory;
	//プレイヤー
	std::shared_ptr<Player> m_player;
	DrawCommand m_command;
};