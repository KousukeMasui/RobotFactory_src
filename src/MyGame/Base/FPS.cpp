#include "FPS.h"
#include<DxLib.h>
FPS::FPS(float fps)
	: fps(fps)
	, AverageCount(60)
	, frameTime(AverageCount)
	, counter(0)
	, startTime(0)
{
}

FPS::~FPS()
{
}

void FPS::Update()
{
	if (counter == 0) {
		startTime = GetNowCount();
	}
	if (counter == AverageCount) {
		int t = GetNowCount();
		frameTime = 1000.0f / ((t - startTime) / static_cast<float>(AverageCount));
		counter = 0;
		startTime = t;
	}
	++counter;
}

void FPS::Draw()
{
	DrawFormatString(0, 0, GetColor(255, 255, 255), "SetFPS = %.1f : NowFPS = %.1f : frameTime = %.3f", fps, frameTime, GetFrameTime());
}

float FPS::GetFrameTime()
{
	return fps/ frameTime;
}

void FPS::Wait()
{
	int tookTime = GetNowCount() - startTime;	//‚©‚©‚Á‚½ŽžŠÔ
	int waitTime = counter * 1000 / fps - tookTime;	//‘Ò‚Â‚×‚«ŽžŠÔ
	if (waitTime > 0) {
		Sleep(waitTime);	//‘Ò‹@
	}
}