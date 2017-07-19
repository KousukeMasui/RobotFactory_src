#pragma once


#include"Base/Manager/TemplateManager.h"
class UnitFactory;
struct FactoryParam;
typedef TemplateManager<InfluenceID, UnitFactory, FactoryParam> FactoryManager;