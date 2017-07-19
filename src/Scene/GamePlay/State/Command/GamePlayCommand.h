#pragma once

#include"Base/Manager/State/IState.h"
#include<memory>
#include"../GamePlayStateID.h"
class World;
class SelectCursor;
class FactoryUI;
//�H��̋����R�}���h�X�e�[�g
class GamePlayCommand : public IState
{
public:
	explicit GamePlayCommand(World& world);
	~GamePlayCommand();

	void Initialize() override;
	void Update(float deltaTime) override;
	void Draw() const override;
	void End() override;
	int Next() const override;
	bool IsEnd() const override;

private:
	World& m_world;
	//�H��UI
	std::shared_ptr<FactoryUI> m_factoryUI;

	GamePlayStateID m_nextID;
	bool m_isEnd;
};