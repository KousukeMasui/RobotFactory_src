#include<DxLib.h>
#include"MyGame/MyGame.h"

int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nCmdShow)
{
	return MyGame("MyGame").Run();
}