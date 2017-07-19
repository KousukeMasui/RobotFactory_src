#pragma once

class World;
class FollowCamera;
#include<memory>
#include"Model/Model/Model.h"
#include"Base/GameUsing.h"
class LerpCursor;
enum class CameraTarget
{
	UNIT,
	CURSOR
};

//デバッグモードの際のカメラの設定や描画を行うクラス
class Debug
{
public:
	//コンストラクタ
	Debug(World& world,LerpCursor& cursor);
	//デストラクタ
	~Debug();
	//現在デバッグ中か
	bool IsDebug();
	//更新
	void Update(float deltaTime);
	//描画
	void Draw() const;
private:
	//デバッグ初期化処理
	void Init();
	//デバッグ終了関数
	void End();
	//デバッグ切り替え
	void ChangeDebug();
	//ユニット切り替え
	void ChangeUnit();
	//カメラのターゲットを変更するa
	void CameraTargetChange();
private:
	World& m_world;
	std::shared_ptr<FollowCamera> m_camera;
	bool m_isDebug;//デバッグ中true
	UnitPtr m_targetUnit;
	Model m_unitTarget;
	CameraTarget m_target;
	LerpCursor& m_cursor;
};