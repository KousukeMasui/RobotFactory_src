#include "CursorState.h"

CursorState::CursorState(LerpCursor * cursor, const UnitPtr & unit):
	m_cursor(cursor),
	m_unit(unit)
{
}

CursorState::~CursorState()
{
}
