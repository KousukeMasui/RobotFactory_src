#pragma once
#include"Base/Manager/State/IState.h"
#include"Base/GameUsing.h"
class Player;
class IWorld;
class PlayerSelectState : public IState
{
public:
	PlayerSelectState(IWorld& world,Player* player);
	~PlayerSelectState();
	void Initialize() override;
	void Update(float deltaTime) override;
	void Draw() const override;
	void End() override;
	int Next() const override;
	bool IsEnd() const override;
private:
	IWorld& m_world;
	Player* m_player;

	bool m_isEnd;
};