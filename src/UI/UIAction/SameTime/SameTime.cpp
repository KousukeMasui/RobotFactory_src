#include "SameTime.h"
#include <stdarg.h>

SameTime::SameTime(int actionSize, ...)
{
	va_list args;

	std::shared_ptr<UIAction> value;
	if (actionSize < 1) return;

	va_start(args, actionSize);

	for (int i= 0; i < actionSize; i++) {
		value = va_arg(args, std::shared_ptr<UIAction>);

		m_actions.push_back(value);
	}
	va_end(args);
}

SameTime::SameTime(const std::vector<std::shared_ptr<UIAction>>& actions):
	m_actions(actions)
{
}

SameTime::~SameTime()
{
}

bool SameTime::Update(UI* ui, float deltaTime)
{
	bool result = true;
	for (auto action : m_actions)
	{
		//‘S•”‚ªI‚í‚Á‚½‚çtrue
		if (!action->Update(ui, deltaTime))
			result = false;
	}
	return result;
}
