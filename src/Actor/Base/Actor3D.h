#ifndef _ACTOR_H_
#define _ACTOR_H_

#include<string>
#include<dxlib.h>
#include<functional>
#include<forward_list>
#include "ActorPtr.h"
#include"Math/Matrix/MyMatrix4.h"
#include"Math\Converter.h"
#include<vector>
#include"Math/Shapes/3D/Shape3D.h"
#include"Math/Shapes/Shapes.h"
#include<map>
#include"Model/AnimationModel/AnimationModel.h"
#include"Math/Collision/HitInfo/HitInfo.h"
class IWorld;
enum class EventMessage;

//アクタークラス
class Actor3D
{
public:
	//コンストラクタ
	Actor3D(IWorld& world, const std::string& name, const MyVector3& position);
	

	//コンストラクタ
	explicit Actor3D(const std::string& name = "none");

	//デストラクタ
	virtual ~Actor3D(){}


	//更新
	void Update(float deltaTime);
	//描画
	void Draw() const;

	//衝突判定
	void Collide(Actor3D& other);

	//死亡しているか?
	bool IsDead() const;

	//死亡する
	void Dead();

	//名前を返す
	const std::string& GetName() const;

	//座標を返す
	MyVector3 GetPosition() const;
	MyVector3 GetVelocity() const;

	void SetPosition(MyVector3 sPos);
	MyMatrix4 GetRotate() const;

	std::map<Shape2DEnum, std::vector<std::shared_ptr<Shape2D>>>  GetShapes2D()const;
	std::map<Shape3DEnum, std::vector<std::shared_ptr<Shape3D>>>  GetShapes3D()const;

	//変換行列を返す
	MyMatrix4 GetPose() const;

	//子の検索
	ActorPtr FindChildren(const std::string& name);
	//子の検索
	ActorPtr FindChildren(std::function<bool(const Actor3D&)>fn);

	//子同士の衝突判定
	void CollideChildren(Actor3D& other);
	//兄弟同士の衝突判定
	void CollideSibling();

	//子の追加
	void AddChild(const ActorPtr& child);
	//全ての子の取得
	std::vector<ActorPtr> GetChilds();
	//子を巡回
	void EachChildren(std::function<void(Actor3D&)> fn);
	//子を巡回(const版)
	void EachChildren(std::function<void(const Actor3D&)> fn) const;

	//子を削除する
	void RemoveChildren(std::function<bool(Actor3D& actor)>fn);
	//子を削除する
	void RemoveChildren();
	//子を強制削除する
	void ClearChildren();
	//メッセージ処理
	void HandleMessage(EventMessage message, void* param);

	void Translate(const MyVector3& velocity);

	//コピー禁止
	Actor3D(const Actor3D& other) = delete;
	Actor3D& operator=(const Actor3D& other) = delete;
private:
	//メッセージ処理
	virtual void OnMessage(EventMessage message, void* param);
	//更新
	virtual void OnUpdate(float deltaTime);
	//描画
	virtual void OnDraw() const;
	//衝突した
	virtual void OnCollide(Actor3D& other, const HitInfo& info);

	//衝突判定 それぞれ当たり判定が異なるので 押し出し処理があるので引数追加
	virtual bool IsCollide(const Actor3D& other,HitInfo& info)const;

protected:
	//ワールド
	IWorld*			m_world;
	//名前
	std::string		m_name;
	//座標
	MyVector3		m_position;

	//移動方向
	MyVector3 m_velocity;
	//回転
	
	MyMatrix4		m_rotate;
	//死亡フラグ
	bool			m_isDead;
	//当たり判定用図形 複雑な形にも対応するためにvectorに格納
	std::map<Shape2DEnum, std::vector<std::shared_ptr<Shape2D>>> m_shapes2DMap;
	std::map<Shape3DEnum, std::vector<std::shared_ptr<Shape3D>>> m_shapes3DMap;
private:
	//子アクター
	std::forward_list<ActorPtr> children_;

};

#endif