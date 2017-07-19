#ifndef	 _MY_GAME_H_
#define	 _MY_GAME_H_

#include"../Scene/Base/SceneManager.h"
#include"Input/Input.h"
#include"Base\FPS.h"
#include"World/World.h"
#include<memory>
class MyGame
{
public:
	MyGame(const char* windowName="window", bool isFullScreen=false);
	int Run();
private:
	bool EffekseerInit();
	bool Initialize();
	void Update(float deltaTime);
	void Draw();
	void End();

private:
	//ワールドクラス
	std::shared_ptr<World> m_world;
	bool m_isEnd;
	SceneManager m_sceneManager;

	FPS m_fps;
	bool m_isWin;
};

#endif
