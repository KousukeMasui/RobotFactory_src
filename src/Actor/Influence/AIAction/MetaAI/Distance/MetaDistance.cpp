#include "MetaDistance.h"
#include"Manager/GameManager.h"
#include"Actor/UnitFactory/UnitFactory.h"
MetaDistance::MetaDistance():
	m_manager(nullptr)
{
}

MetaDistance::~MetaDistance()
{
}

void MetaDistance::Start(GameManager * manager)
{
	m_manager = manager;
}

void MetaDistance::Clear()
{
	//距離計算結果を削除
	m_distanceData.clear();
}

UnitPtr MetaDistance::GetNearUnitOtherInfluence(const Unit & unit, const std::function<bool(const Unit& unit)>& searchFunc)
{
	std::function<bool(const Unit& unit)> func = searchFunc;
	if (func == nullptr) func = [](const Unit& unit) {return true; };
	auto units = m_manager->GetUnitManager().GetOtherFunction(unit.GetInfluence(),func);
	return NearUnit(unit,units);
}

UnitPtr MetaDistance::GetNearUnitInfluence(const Unit & unit, const std::function<bool(const Unit& unit)>& searchFunc)
{
	std::function<bool(const Unit& unit)> func = searchFunc;
	if (func == nullptr) func = [](const Unit& unit) {return true; };
	auto units = m_manager->GetUnitManager().GetFunction(unit.GetInfluence(), func);
	return NearUnit(unit, units);
}

LiftObjectPtr MetaDistance::GetNearLift(const Unit & unit, const std::function<bool(const LiftObject& lift)>& searchFunc)
{
	std::function<bool(const LiftObject& lift)> func = searchFunc;
	if (func == nullptr) func = [](const LiftObject& lift) {return true; };
	LiftObjects lifts;
	auto parts = m_manager->GetPartsManager().All();
	for (auto p : parts)
		if(func(*p)) lifts.push_back(p);
	//死んでいるユニットを検索
	auto units = m_manager->GetUnitManager().GetFunction([&](const Unit& unit) {
		return func(unit) && unit.IsDead();
	});;
	for (auto u : units)
		lifts.push_back(u);

	return NearLeft(unit,lifts);
}
UnitPtr MetaDistance::GetNearUnit(const Unit & unit)
{
	auto units = m_manager->GetUnitManager().All();
	return NearUnit(unit, units);
}

float MetaDistance::Distance(const Object& o1, const Object& o2)
{
	void* v1 = (void*)&o1;
	void* v2 = (void*)&o2;
	if (!IsFindThisFrame(v1, v2)) return DistanceCalc(o1, o2);
	return GetDistance(v1,v2);
}

float MetaDistance::Distance(const LiftObject & l, UnitFactory* f)
{
	void* v1 = (void*)&l;
	void* v2 = (void*)f;
	if (!IsFindThisFrame(v1, v2)) return DistanceCalc(l, f);
	return GetDistance(v1,v2);
}


UnitPtr MetaDistance::NearUnit(const Unit & unit, const UnitPtrs & units)
{
	UnitPtr result = nullptr;
	float min = FLT_MAX;
	for (const auto u : units)
	{

		//同じユニットでは計算をしない
		if (&*u == &unit) continue;

		float distance = Distance(*u, unit);
		if (distance <= min)
		{
			min = distance;
			result = u;
		}

	}
	return result;
}
LiftObjectPtr MetaDistance::NearLeft(const Unit & unit, const LiftObjects & lifts)
{
	//検索対象が１つの場合検索しない
	if (lifts.size() == 1) return lifts.front();
	LiftObjectPtr result = nullptr;
	float min = FLT_MAX;
	for (const auto l : lifts)
	{
		//同じユニットでは計算をしない
		if (&*l == &unit) continue;

		float distance = Distance(*l, unit);
		if (distance <= min)
		{
			min = distance;
			result = l;
		}

	}
	return result;
}
float MetaDistance::DistanceCalc(const Object& o1, const Object& o2)
{
	float distance = MyVector3::Distance(o1.Position(), o2.Position());
	m_distanceData[(void*)&o1][(void*)&o2] = distance;
	return distance;
}
float MetaDistance::DistanceCalc(const LiftObject & l, UnitFactory* f)
{
	float distance = MyVector3::Distance(l.Position(), f->GetParam().Position());
	m_distanceData[(void*)&l][(void*)&f] = distance;
	return distance;
}
bool MetaDistance::IsFindThisFrame(void* v1, void* v2)
{
	//どちらかの順で数値が入っていたらtrue
	return (m_distanceData.count(v1) >= 1 && m_distanceData[v1].count(v2) == 1) ||
		(m_distanceData.count(v2) >= 1 && m_distanceData[v2].count(v1) == 1);
}

float MetaDistance::GetDistance(void * d1, void * d2)
{
	if (m_distanceData.count(d1) >= 1 && m_distanceData[d1].count(d2) == 1)
	{
		return m_distanceData[d1][d2];
	}
	else if (m_distanceData.count(d2) >= 1 && m_distanceData[d2].count(d1) == 1)
	{
		return m_distanceData[d2][d1];
	}
}