#ifndef	  _GAMEPLAY_SCENE_H_
#define	  _GAMEPLAY_SCENE_H_

#include"../Base/IScene.h"
#include"Model/StaticModel/StaticModel.h"
#include<memory>
#include"Base/Manager/State/StateManager.h"
class World;
//�Q�[���v���C�V�[��
class GamePlayScene :public IScene
{
public:
	//�R���X�g���N�^
	explicit GamePlayScene(const std::shared_ptr<World>& world,bool& isWin);
	//�f�X�g���N�^
	~GamePlayScene();

	virtual void Initialize() override;
	virtual void Update(float deltaTime) override;
	void EndUpdate(float deltaTime);
	virtual void Draw()const override;
	void EndDraw() const;

	//�I�����Ă��邩
	virtual bool IsEnd()const override;

	//���̃V�[����Ԃ�
	virtual int Next()const override;

	virtual void End() override;

private:
	std::shared_ptr<World> m_world;

	StateManager m_stateManager;
	bool m_isEnd;

	bool m_isEndEffect;//�I�����̉��o�J�n����true

	bool& m_isWin;//������true
};


#endif