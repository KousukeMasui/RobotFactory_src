#include "Mouse.h"
#include"Math/Converter.h"
#include<DxLib.h>
void Mouse::Initialize()
{
}
void Mouse::Update(float deltaTime)
{
	//配列コピー 交換ではないのでforで行う
	for (int i = 0; i < MouseCommand::MAX; i++)
	{
		isPreviosPress[i] = isCurrentPress[i];
	}
	mouseInput = GetMouseInput();
	isCurrentPress[MouseCommand::LEFT] = ((mouseInput & MOUSE_INPUT_LEFT) != 0);
	isCurrentPress[MouseCommand::RIGHT] = ((mouseInput & MOUSE_INPUT_RIGHT) != 0);
	isCurrentPress[MouseCommand::MIDDLE] = ((mouseInput & MOUSE_INPUT_MIDDLE) != 0);

	if (IsPressState(MouseCommand::LEFT))
	{
		m_effect.Create(Position());
	}
	m_effect.Update(deltaTime);
	m_velocity = Position() - m_prevPosition;
	m_prevPosition = Position();
}

void Mouse::Draw() const
{
	m_effect.Draw();
}

MyVector2 Mouse::Position() const
{
	int x, y;
	GetMousePoint(&x, &y);
	return MyVector2(x,y);
}

MyVector2 Mouse::Velocity() const
{
	return m_velocity;
}

float Mouse::Wheel()
{
	return GetMouseWheelRotVol();
}

Line3D Mouse::ToWorldLine()
{
	MyVector2 mousePosition = Position();
	return Line3D(Converter::VECTORToMyVector3(ConvScreenPosToWorldPos(VGet((int)mousePosition.x, (int)mousePosition.y, 0.0f))),
		Converter::VECTORToMyVector3(ConvScreenPosToWorldPos(VGet((int)mousePosition.x, (int)mousePosition.y, 1.0f))));
}

bool Mouse::IsPressDown(MouseCommand command)
{
	return !isPreviosPress[command] && isCurrentPress[command];
}
//押した位置を第二引数で渡す
bool Mouse::IsPressDown(MouseCommand command, MyVector2 * point)
{
	bool result = IsPressDown(command);
	if (result)
	{
		int r;
		int x, y;
		GetMouseInputLog(&r, &x, &y, true);
	
		point->x = x;
		point->y = y;
	}
	return result;
}

bool Mouse::IsPressState(MouseCommand command)
{
	return isPreviosPress[command] && isCurrentPress[command];
}

bool Mouse::IsPressState(MouseCommand command, MyVector2 * point)
{
	bool result = IsPressState(command);
	if (result)
	{
		int x, y;

		GetMousePoint(&x, &y);

		point->x = x;
		point->y = y;
	}
	return result;
}

bool Mouse::IsPressUp(MouseCommand command)
{
	return isPreviosPress[command] && !isCurrentPress[command];
}

bool Mouse::IsPressUp(MouseCommand command, MyVector2 * point)
{
	bool result = IsPressUp(command);
	if (result)
	{
		int x, y;

		GetMousePoint(&x, &y);

		point->x = x;
		point->y = y;
	}
	return result;
}

