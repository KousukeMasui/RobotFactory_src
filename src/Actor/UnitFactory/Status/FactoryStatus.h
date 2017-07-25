#pragma once

//工場のステータスクラス
#include"Actor\Unit\Base\Status/UnitStatus.h"
#include<functional>
#include<map>
#include"../FactoryStatusID.h"
class FactoryStatus
{
public:
	explicit FactoryStatus(const std::function<void(const UnitStatus& status)>& createFunc);
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
public:
	//工場のHP
	int maxHP;
	float hp;
	int healInterval;

	//ステータス格納マップ
	std::map<FactoryStatusID, int> status;

	int partsCount;//保有する資源数
private:
	//ユニット生成に使う処理を入れる変数
	std::function<void(const UnitStatus& status)>createFunc;
};