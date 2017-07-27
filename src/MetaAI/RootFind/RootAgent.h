#pragma once
#include"Object/Object.h"
#include<functional>
#include<vector>
#include"Model/Model/Model.h"
//経路探索で動くベースクラス
//実際の移動はオブジェクト毎に違う処理を行いたいのでここに処理は書かない
class RootAgent{
public:
	//コンストラクタ
	explicit RootAgent(Object& object);
	//デストラクタ
	~RootAgent();

	//更新
	void Update(float deltaTime,float range);
	//次の経路点への方向ベクトルを返す
	MyVector3 ToNextVelocity() const;
	//オブジェクトを次の経路点へ回転させる
	bool RotateToNext(float deltaTime);
	//経路探索待ちか
	bool IsFindWait() const;
	//経路探索中にする
	void StartFind();
	//経路を与える
	void SetRoot(const MyVector3& position);
	void SetRoot(const std::vector<MyVector3>& root);
	//位置ポインタを返す
	MyVector3* Position();
	//経路が存在するか
	bool IsMove() const;
	//最終到達目標を返す
	const MyVector3 EndPoint() const;
	//経路削除
	void Delete();
	//経路を描画
	void Draw(const Color& color) const;
private:
	//経路探索で移動させるオブジェクト
	Object& m_object;
	//経路保存変数
	std::vector<MyVector3> m_root;
	//経路探索待ちか
	bool m_isFindWait;
	//次の経路点への方向ベクトル
	MyVector3 m_toNextVelocity;
	//経路モデル
	Model m_rootModel;
};