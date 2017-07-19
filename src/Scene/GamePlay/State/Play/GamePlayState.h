#pragma once
#include"Base/Manager/State/IState.h"
#include<memory>
class World;
class GamePlayState : public IState
{
public:
	explicit GamePlayState(std::shared_ptr<World>& world);
	~GamePlayState();

	void Initialize() override;
	void Update(float deltaTime) override;
	void Draw() const override;
	void End() override;
	int Next() const override;
	bool IsEnd() const override;
private:
	std::shared_ptr<World>& m_world;
};