#pragma once
#include"Base/Manager/State/IState.h"
class IWorld;
#include<vector>
#include<memory>
class Unit;
#include"Math/Vector/MyVector3.h"
struct Point2;
#include"Base/GameUsing.h"
#include"../../FactoryStatusAI/FactoryStatusAI.h"
class LerpCursor;
//開始時のAI プレイヤーを攻撃することよりも未所属の工場と資源回収を狙う
class StartState : public IState
{
public:
	StartState(IWorld& world, const Shaft& shaft,LerpCursor* cursor,UnitPtrs& units);
	~StartState();

	virtual void Initialize()override;
	virtual void Update(float deltaTime)override;
	void Draw() const {}
	virtual void End()override;
	virtual int Next() const override;
	virtual bool IsEnd()const override;
private:
	IWorld& m_world;
	std::shared_ptr<FactoryStatusAI> m_statusAI;
	LerpCursor* m_cursor;
	Shaft m_shaft;
};