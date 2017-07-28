#pragma once

#include"../PriorityActionPtr.h"
#include<vector>
#include<functional>
//何か一つ判断材料を軸にして思考させる
//位置、HPなどを一つの式で数値として求めさせてそれとそもそもの優先順位とで比較して判断する
class Shaft
{
public:
	//コンストラクタ
	Shaft();
	//デストラクタ
	~Shaft();
	//切り替え処理を設定
	void SetChangeFunc(const std::function<void()>& changeFunc);
	//初期化
	void Initialize();
	//更新
	bool Update(float deltaTime);
	//描画　デバッグ用
	void DebugDraw() const;
	//行動追加
	void Add(const PriorityActionPtr& action);
private:
	//最も条件に等しいアクションの取得
	void Change();
private:
	PriorityActionPtr m_nowAction;
	std::vector<PriorityActionPtr> m_actions;

	//AIの切り替え時に動かしたい処理
	std::function<void()> m_changeFunc;
};