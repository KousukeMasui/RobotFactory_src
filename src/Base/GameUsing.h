#pragma once
#include<memory>
#include<vector>
#include<map>
#include"Actor\Influence\InfluenceID.h"
//このゲームで良く使用する長い型名をusingするクラス
//ユニット
class Unit;
using UnitPtr = std::shared_ptr<Unit>;
using UnitPtrs = std::vector<UnitPtr>;
//工場
class UnitFactory;
using FactoryPtr = std::shared_ptr<UnitFactory>;
using FactoryPtrs = std::vector<FactoryPtr>;
//資源
class Parts;
using PartsPtr = std::shared_ptr<Parts>;
using PartsPtrs = std::vector<PartsPtr>;

//工場分割変数
using FactoryMap = std::map<InfluenceID, FactoryPtrs>;

class LiftObject;
enum class LIFT_ID;
using LiftObjectPtr = std::shared_ptr<LiftObject>;
using LiftObjects = std::vector<LiftObjectPtr>;
using LiftObjectsMap = std::map<LIFT_ID, LiftObjects>;
