#pragma once

class FPS {
public:
	explicit FPS(float fps = 60);
	~FPS();

	void Update();
	void Draw();
	float GetFrameTime();
	void Wait();

private:
	const float fps;
	const int AverageCount;
	float frameTime;
	int counter;
	int startTime;
};