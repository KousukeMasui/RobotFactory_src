#pragma once
#include"Math/Vector/MyVector2.h"
#include"Math/Shapes/3D/Line/Line3D.h"
#include"Effect\MouseEffect.h"
#include<memory>
enum MouseCommand
{
	LEFT = 0,
	RIGHT,
	MIDDLE,
	MAX
};

class Mouse
{
private:
	Mouse() = default;
	~Mouse() = default;

public:
	Mouse(const Mouse&) = delete;
	Mouse& operator=(const Mouse&) = delete;
	Mouse(Mouse&&) = delete;
	Mouse& operator=(Mouse&&) = delete;

	static Mouse& GetInstance()
	{
		static Mouse inst;
		return inst;
	}

	void Initialize();
	void Update(float deltaTime);

	void Draw() const;//エフェクト表示

	//現在のマウスの位置を返す
	MyVector2 Position() const;
	//マウスの1フレーム当たりの移動量を返す(正規化はしていません。)
	MyVector2 Velocity() const;
	float Wheel();



	//マウスの位置からラインを生成
	Line3D ToWorldLine();

	bool IsPressDown(MouseCommand command);
	bool IsPressDown(MouseCommand command,MyVector2* point);
	bool IsPressState(MouseCommand command);
	bool IsPressState(MouseCommand command, MyVector2* point);
	bool IsPressUp(MouseCommand command);
	bool IsPressUp(MouseCommand command,MyVector2* point);
private:
	bool isCurrentPress[3]; //今のフレームに押された時true
	bool isPreviosPress[3]; //1フレーム前に押された時true
	MouseEffect m_effect;
	//マウスのインプット情報
	int mouseInput;
	//マウスの移動量
	MyVector2 m_velocity;
	//マウスの更新前の位置
	MyVector2 m_prevPosition;
};