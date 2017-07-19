#pragma once
#include"Base/GameUsing.h"
#include"Base/Manager/State/IState.h"
class LerpCursor;
class CursorState : public IState
{
public:
	CursorState(LerpCursor* cursor, const UnitPtr& unit);
	~CursorState();
protected:

	LerpCursor* m_cursor;
	UnitPtr m_unit;
};