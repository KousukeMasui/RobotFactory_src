#include "ToUnitState.h"
#include"Cursor\LerpCursor.h"
#include"Actor/Unit/Unit.h"
#include"../../CursorStateID.h"
ToUnitState::ToUnitState(LerpCursor* cursor, const UnitPtr & target):
	CursorState(cursor,target)
{
}

ToUnitState::~ToUnitState()
{
}

void ToUnitState::Initialize()
{
}

void ToUnitState::Update(float deltaTime)
{
	m_cursor->SetPosition(m_unit->Position());
	m_cursor->Update(deltaTime);
}

void ToUnitState::Draw() const
{
}

void ToUnitState::End()
{
}

int ToUnitState::Next() const
{
	return (int)CursorStateID::TO_TARGET;
}

bool ToUnitState::IsEnd() const
{
	return m_cursor->IsCollide(m_unit->GetSphere());
}
