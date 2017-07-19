#pragma once

#include"Base/Manager/State/IState.h"
#include"Base/GameUsing.h"
class FactoryStatusAI;
class IWorld;
#include"Base/AI/Priority/Shaft/Shaft.h"
class LerpCursor;
//工場を確保後のAI パーツ回収とユニット強化を主に行う
//ここから攻撃AIを作成する
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
	//守りが少ない工場を攻撃するAI
	bool WeakFactoryAttack(UnitPtrs& units,const FactoryPtrs& myFactorys);
private:
	IWorld& m_world;
	//前線とそれ以外で上げるステータスを変更するので
	std::shared_ptr<FactoryStatusAI> m_frontStatusAI;
	std::shared_ptr<FactoryStatusAI> m_backStatusAI;

	Shaft m_shaft;

	//カーソル
	LerpCursor* m_cursor;
};