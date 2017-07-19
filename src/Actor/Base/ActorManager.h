#ifndef	 _ACTOR_MANAGER_H_
#define	 _ACTOR_MANAGER_H_

#include<unordered_map>
#include"ActorPtr.h"
#include"Actor3D.h"

enum class ActorGroup;
//アクターマネージャー
class ActorManager
{
public:
	//コンストラクタ
	ActorManager();
	//初期化
	void Initialize();
	//更新
	void Update(float deltaTime);
	//描画
	void Draw() const;
	//アクターの追加
	void AddActor(ActorGroup group, const ActorPtr& actor);
	//アクターの検索
	ActorPtr FindActor(const std::string& name);
	std::vector<ActorPtr> FindActors(const ActorGroup& group);
	//メッセージ処理
	void HandleMessage(EventMessage message, void* param);
	//
	ActorManager(const ActorManager& other) = delete;
	ActorManager& operator=(const ActorManager& other) = delete;

	void Clear();
private:
	//衝突判定
	void Collide();
private:
	//ルートノード
	Actor3D m_root;
	//アクターグループ
	std::unordered_map<ActorGroup, ActorPtr> m_actors;

};

#endif