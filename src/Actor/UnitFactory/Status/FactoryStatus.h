#pragma once

//工場のステータスクラス
#include"Actor\Unit\Base\Status/UnitStatus.h"
#include<functional>
#include<map>
#include"../FactoryStatusID.h"
#include"Create/UnitCreate.h"
class CSVData;
class IWorld;
class RootFind;
struct FactoryParam;
class FactoryStatus
{
public:
	explicit FactoryStatus(IWorld& world,RootFind& find,FactoryParam& param);
	//生成時のステータスにして返す
	UnitStatus CreateStatus(GameManager* manager) const;
	//生成に必要な資源数を求めて返す
	int CreatePartsCount() const;

	//工場を含めた合計ステータスを返す
	int Total() const;
	//強化可能か
	bool IsStatusUp(FactoryStatusID status);
	//強化関数
	void StatusUp(FactoryStatusID status,GameManager* manager);

	void Create(const UnitStatus& status);
public:
	//工場のHP
	float maxHP;
	float hp;
	int healInterval;

	//ステータス格納マップ
	std::map<FactoryStatusID, int> status;

	int partsCount;//保有する資源数
private:
	UnitCreate m_create;
};