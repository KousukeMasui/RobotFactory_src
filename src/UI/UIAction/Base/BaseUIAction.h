#pragma once
class UI;
template<typename UIClass>
class BaseUIAction {
public:
	BaseUIAction() {};
	virtual bool Update(UIClass* ui, float deltaTime) = 0;
};