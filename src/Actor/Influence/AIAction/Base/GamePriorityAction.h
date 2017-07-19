#pragma once

#include"Base/AI/Priority/PriorityAction.h"
class IWorld;
enum class InfluenceID;
class LerpCursor;
#include"Base/GameUsing.h"
#include"Base/Manager/State/StateManager.h"
//今回のゲーム用のPriorityAction継承クラス
class GamePriorityAction : public PriorityAction
{
public:
	GamePriorityAction(float priority, IWorld& world,InfluenceID id, LerpCursor* cursor,UnitPtrs& units);
	~GamePriorityAction();
protected:
	IWorld& m_world;
	InfluenceID m_influenceID;
	//命令用カーソルポインタ
	LerpCursor* m_cursor;
	//ユニット変数参照
	UnitPtrs& m_units;
	//実際に命令するユニット
	UnitPtr m_orderUnit;
	StateManager m_cursorManager;
	//距離で優先度を設定する際にこれ - 距離の数値を返す
	const float m_distancePriority;
};