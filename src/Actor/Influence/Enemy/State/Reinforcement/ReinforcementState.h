#pragma once

#include"Base/Manager/State/IState.h"
#include"Base/GameUsing.h"
#include"../../FactoryStatusAI/FactoryStatusAI.h"
class IWorld;
#include"Base/AI/Priority/Shaft/Shaft.h"
class LerpCursor;
//工場を確保後のAI
class ReinforcementState : public IState
{
public:
	ReinforcementState(IWorld& world, const Shaft& shaft, LerpCursor* cursor, UnitPtrs& units);
	~ReinforcementState();

	virtual void Initialize()override;
	virtual void Update(float deltaTime)override;
	void Draw() const {}
	virtual void End()override;
	virtual int Next()const override;
	virtual bool IsEnd()const override;
private:
	//強化関数
	void PowerUp();
private:
	IWorld& m_world;
	//前線とそれ以外で上げるステータスを変更するので
	FactoryStatusAI m_frontStatusAI;
	FactoryStatusAI m_backStatusAI;

	Shaft m_shaft;

	//カーソル
	LerpCursor* m_cursor;
};