#pragma once

//優先度付きAI行動親クラス
class PriorityAction
{
public:
	//コンストラクタ
	explicit PriorityAction(float priority);
	//デストラクタ
	~PriorityAction() {};

	//初期化
	virtual void Initialize() = 0;
	//更新
	virtual void Update(float deltaTime) = 0;
	//描画
	virtual void Draw()const {}
	virtual void End() = 0;
	float Priority();
	bool IsEnd() const;
protected:
	//優先度を+αで計算する関数
	virtual float OnPriority() = 0;
protected:
	bool m_isEnd;//終了したか
private:
	//優先度
	float m_priority;
};