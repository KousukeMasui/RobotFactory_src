#pragma once

class IState
{
public:
	virtual ~IState() {};
	virtual void Initialize() = 0;
	virtual void Update(float deltaTime) = 0;
	virtual void Draw() const = 0;
	virtual void End() = 0;
	virtual int Next() const= 0;
	virtual bool IsEnd() const = 0;
};