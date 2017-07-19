#include "Parts.h"
#include"Actor\Base\IWorld.h"

#include"Actor/UnitFactory/UnitFactory.h"
#include"Manager\GameManager.h"
#include"Base/RoadFinder/PathFind3DUtility.h"
#include"Actor/UnitFactory/UnitFactory.h"
#include"Math/Shapes/Renderer/ShapeRenderer.h"
const float PARTS_RANGE = 50.0f;

Parts::Parts(IWorld& world, const MyVector3 & position) :
	LiftObject(LIFT_ID::PARTS, position + MyVector3(0, 8.0f, 0.0f)),
	m_world(world),
	m_model(MODEL_ID::PARTS),
	m_isDelete(false),
	m_sphere(position, 10.0f)
{
}

Parts::~Parts()
{
}

bool Parts::IsDelete() const
{
	return m_isDelete;
}

void Parts::LiftDown(FactoryPtr factory)
{
	factory->PartsCount(5);
	m_isDelete = true;
}
Sphere Parts::GetSphere() const
{
	return m_sphere;
}
void Parts::Draw() const
{
	m_model.Draw(MyMatrix4::Scale(9.0f, 9.0f, 9.0f) * MyMatrix4(m_rotate).SetPosition(m_position));
}
