#pragma once
class IWorld;
#include"Base/Manager/State/StateManager.h"
#include<vector>
#include"Math/Point2/Point2.h"

#include<map>
#include"Base/GameUsing.h"

#include"Cursor/LerpCursor.h"
#include"../Base/Influence.h"
class Enemy : public Influence
{
public:
	explicit Enemy(IWorld& world);
	~Enemy();

	void Update(float deltaTime) override;
	void Draw() const override;

	LerpCursor& Cursor();

private:
	//命令するユニットを設定する
	void OrderUnitSet();

private:
	//AIのステートパターンの統括クラス
	StateManager m_stateManager;

	//カーソルクラス
	LerpCursor m_cursor;
	UnitPtrs m_units;
};