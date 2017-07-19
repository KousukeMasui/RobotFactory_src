#include "AddTextAction.h"
AddTextAction::AddTextAction(const char* startText, const char* addText, float addTime, bool isLoop):
	m_startText(startText),
	m_addText(addText),
	m_addTime(addTime),
	m_addTimer(0.0f),
	m_drawIndex(0),
	m_isLoop(isLoop)
{
	
}

AddTextAction::~AddTextAction()
{
}

bool AddTextAction::OnUpdate(FontSprite* font, float deltaTime)
{
	m_addTimer += deltaTime;
	if (m_addTimer >= m_addTime)
	{
		
		m_addTimer = 0.0f;
		if (m_drawIndex >= strlen(m_addText)) {
			m_drawIndex = 0;
			font->ChangeText(m_startText);
			return false;
		}
		font->ChangeText(font->GetText() + m_addText[m_drawIndex++]);

		if (m_drawIndex >= strlen(m_addText)) {
			if (m_isLoop)
				return false;
			return true;
		}
	}
	return false;
}