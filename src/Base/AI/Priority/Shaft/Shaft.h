#pragma once

#include"../PriorityActionPtr.h"
#include<vector>
//何か一つ判断材料を軸にして思考させる
//位置、HPなどを一つの式で数値として求めさせてそれとそもそもの優先順位とで比較して判断する
class Shaft
{
public:
	//コンストラクタ
	Shaft();
	//デストラクタ
	~Shaft();
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
};