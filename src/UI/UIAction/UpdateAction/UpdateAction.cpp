#include "UpdateAction.h"

UpdateAction::UpdateAction(const std::function<void(UI* ui)>& func):
	m_Func(func)
{
}

UpdateAction::~UpdateAction()
{
}

bool UpdateAction::Update(UI* ui, float deltaTime)
{
	if (m_Func == nullptr) return false;

	m_Func(ui);

	return false;
}
