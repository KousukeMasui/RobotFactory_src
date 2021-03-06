#pragma once
#include<memory>
#include"../LiftObject/LiftObject.h"
#include"../Influence/InfluenceID.h"
#include"Base/Manager/Tree/Tree.h"
#include"Base/Status/UnitStatus.h"
#include"Effect/EffectPtr.h"
#include"Math/Shapes/3D/Capsule/Capsule.h"
#include"Model/AnimationModel/AnimationModel.h"
#include"ToUnit/ToUnit.h"
#include<functional>
#include"MetaAI/RootFind/RootAgent.h"
class IWorld;
//画面上に命令を出した際に動くキャラクター
//所属変わるときは一回パラメータを取得してから一回殺して再生成する
class Unit : public LiftObject
{
public:
	Unit(IWorld& world,RootFind& find, InfluenceID influence,const MyVector3& position,const UnitStatus& status);
	~Unit();
	//ステータスを返す
	UnitStatus& GetStatus();
	//プレイヤーの選択当たり判定
	bool IsCollide(const Line3D& line);
	//現在のビヘイビアのIDを返す
	int NodeID() const;
	//描画
	void Draw() const;
	//勢力を返す
	InfluenceID GetInfluence() const;
	//メッセージを受け取る
	void Message(int messageID,void* data) override;
	//削除するか
	bool IsDelete() const override;
	//死んでいるか
	bool IsDead() const;
	//工場に置かれた際の処理
	void LiftDown(FactoryPtr factory) override;
	//ユニットとの当たり判定
	bool IsCollide(const Unit& other);
	//当たった場合の処理
	void Collide(Unit& other);
	//当たり判定用図形を返す
	Sphere GetSphere() const override;
	//更新
	void Update(float deltaTime);
	//移動設定
	void Move(const MyVector3& velocity);
	//Manager設定関数
	Unit& GetParam();
	//運んでいるオブジェクトを返す
	LiftObject* GetLift();
	//アニメーションモデルを返す
	AnimationModel& GetModel();

	RootAgent& Agent();
	//方向指定の回転処理
	bool RotateVelocity(const MyVector3& velocity,float deltaTime);
private:
	//回復
	void Heal(float value);
private:
	IWorld& m_world;
	//削除するか
	bool m_isDelete;
	//ビヘイビアツリー
	Tree m_AITree;
	//現在のノードID
	int m_nodeID;
	//アニメーション用モデル
	AnimationModel m_model;
	Capsule m_capsule;
	//勢力
	InfluenceID m_influence;
	//工場によって変わるステータス
	UnitStatus m_status;
	//運んでいる物体
	std::shared_ptr<LiftObject> m_liftObject;
	//ユニット追従クラス
	ToUnit m_toUnit;

	//経路探索
	RootAgent m_rootAgent;
};