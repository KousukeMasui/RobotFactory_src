#include "SelectCursor.h"
#include"Math/Shapes/Renderer/ShapeRenderer.h"
#include"Actor/Unit/Unit.h"
#include"World/World.h"
#include"Actor/UnitFactory/UnitFactory.h"
SelectCursor::SelectCursor(const MyVector3 & position):
	Object(position,MyMatrix4::Identity()),
	m_model(MODEL_ID::CIRCLE),
	m_sphere(position,20.0f),
	m_scale(20,1,20)
{
}

SelectCursor::~SelectCursor()
{
}

void SelectCursor::Update(float deltaTime)
{
	OnUpdate(deltaTime);
	m_sphere.m_center = m_position;

	m_rotate *= MyMatrix4::RotateY(Converter::DegToRad(deltaTime));
}

void SelectCursor::SetPosition(const MyVector3 & position)
{
	m_position = position;
	m_position.y = 0.0f;
}

void SelectCursor::Draw(const Color & color) const
{
	m_model.SetMaterialColor(0, color);
	m_model.Draw(m_position + MyVector3(0, 2, 0), m_scale, m_rotate);
}

UnitPtr SelectCursor::IsCollide(IWorld & world, InfluenceID id) const
{
	UnitPtr result = IsCollide(world.GetGameManager().GetUnitManager().GetVector(id));
	if (result == nullptr)
		result = IsCollide(world.GetGameManager().GetUnitManager().GetOther(id));
	return result;
}

UnitPtr SelectCursor::IsCollide(const UnitPtrs & units) const
{
	for (auto unit : units)
	{
		if (IsCollide(unit->GetSphere()))
			return unit;
	}
	return nullptr;
}
FactoryPtr SelectCursor::IsCollide(const FactoryPtrs & factorys) const
{
	for (auto factory : factorys)
	{
		if (IsCollide(&*factory))
			return factory;
	}
	return nullptr;
}
bool SelectCursor::IsCollide(const UnitFactory* factory) const
{
	return (factory->IsCollide(m_sphere, HitInfo()));
}
Sphere SelectCursor::GetSphere() const
{
	return m_sphere;
}
bool SelectCursor::IsCollide(const Sphere & sphere) const
{
	return m_sphere.IsCollide(sphere);
}

void SelectCursor::Scale(const MyVector3 & scale)
{
	m_scale = scale;
}
