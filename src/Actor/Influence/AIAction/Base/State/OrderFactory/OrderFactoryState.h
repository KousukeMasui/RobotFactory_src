#pragma once
#include"../CursorState.h"
class IWorld;
#include"Math/Point2/Point2.h"
#include"Math/Vector/MyVector3.h"
//ユニットを資源orユニットまで移動する命令を出す
class OrderFactoryState : public CursorState
{
public:
	OrderFactoryState(IWorld& world,LerpCursor* cursor,const UnitPtr& unit,UnitFactory* factory,InfluenceID influence);
	~OrderFactoryState();
	void Initialize() override;
	void Update(float deltaTime) override;
	void Draw() const override;
	void End() override;
	int Next() const override;
	bool IsEnd() const override;
private:
	IWorld& m_world;
	UnitFactory* m_factory;
	//直進するか
	bool m_isStraight;
	std::vector<Point2> m_root;
	InfluenceID m_influence;
};