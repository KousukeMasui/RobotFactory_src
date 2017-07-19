#pragma once
#include<memory>
#include"../LiftObject/LiftObject.h"
#include"../Influence/InfluenceID.h"
#include"Tree/Tree.h"
#include"Base/Status/UnitStatus.h"
#include"Effect/EffectPtr.h"
#include"Math/Shapes/3D/Capsule/Capsule.h"
#include"Model/AnimationModel/AnimationModel.h"
#include<functional>
class IWorld;
//画面上に命令を出した際に動くキャラクター
//所属変わるときは一回パラメータを取得してから一回殺して再生成する
class Unit : public LiftObject
{
public:
	Unit(IWorld& world, InfluenceID influence,const MyVector3& position,const UnitStatus& status);
	~Unit();
	//生成された際の処理
	void CreateAI(const std::function<void()>& createFunc);
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

	//経路削除
	void RoadDelete();
	//更新
	void Update(float deltaTime);
	//移動設定
	void Move(const MyVector3& velocity);
	//Manager設定関数
	Unit& GetParam();
	//現在移動中か
	bool IsMove() const;
	//運んでいるオブジェクトを返す
	LiftObject* GetLift();
	//移動方向を返す
	MyVector3 GetVelocity() const;
	//アニメーションモデルを返す
	AnimationModel& GetModel();

	//回転　移動方向を向く 回転が終わったらtrue
	bool LerpToVelocity(const MyVector3& velocity);

	MyVector3 ToNextVelocity() const;
	//目的地を返す
	MyVector3 Target() const;
private:
	//回復
	void Heal(float value);
	//経路探索用メッセージ
	void RootMessage(int messageID, void* data);
	//移動方向を設定する
	void SetVelocity();
private:
	IWorld& m_world;
	//目的地までの道
	std::vector<MyVector3> m_roadPositions;

	bool m_isDelete;
	//ビヘイビアツリー
	Tree m_AITree;
	//現在のノードID
	int m_nodeID;
	//アニメーション用モデル
	AnimationModel m_model;
	//当たり判定用図形
	Sphere m_sphere;
	Capsule m_capsule;
	//勢力
	InfluenceID m_influence;
	//工場によって変わるステータス
	UnitStatus m_status;
	//運んでいる物体
	std::shared_ptr<LiftObject> m_liftObject;
	//移動量
	MyVector3 m_velocity;
	//停止時実行関数
	std::function<void()> m_stopFunc;
};