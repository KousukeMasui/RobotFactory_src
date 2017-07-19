#include "Link.h"
#include <stdarg.h>

Link::Link(int actionSize, bool isLoop, ...):
	m_actionSize(actionSize),
	m_actionIndex(0),
	m_isLoop(isLoop)
{
	va_list args;
	int count;
	std::shared_ptr<UIAction> value;
	if (actionSize < 1) return;

	va_start(args, isLoop);

	for (count = 0; count < actionSize; count++) {
		value = va_arg(args, std::shared_ptr<UIAction>);

		m_actions.push_back(value);
	}
	va_end(args);
}

Link::Link(std::vector<std::shared_ptr<UIAction>> actions, bool isLoop):
	m_actions(actions),
	m_isLoop(isLoop),
	m_actionIndex(0)
{
	m_actionSize = actions.size();
}

Link::~Link()
{
}

bool Link::Update(UI * ui, float deltaTime)
{
	if (m_actions[m_actionIndex]->Update(ui, deltaTime))
	{
		m_actionIndex++;
		if (m_actionIndex >= m_actionSize)
		{
			if (m_isLoop)
			{
				m_actionIndex = 0;
			}
			else
				return true;
		}
	}
	return false;
}
