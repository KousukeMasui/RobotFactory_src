#pragma once
#include"Distance\MetaDistance.h"
#include"Overlap/OverlapData.h"
#include"RootFind/RootFind.h"
#include"Math/Point2/Point2.h"
class GameManager;
class MetaAI
{
public:
	//コンストラクタ
	MetaAI();
	//デストラクタ
	~MetaAI();
	//ゲーム開始
	void Start(GameManager* manager);
	//更新
	void Update();
	//引数以外のユニットの位置
	std::vector<Point2> GetUnitPoints(const Unit& unit);
	//距離クラス
	MetaDistance& Distance();
	//重複チェッククラス
	OverlapData& Overlap();
	RootFind& GetFind();
private:
	GameManager* m_manager;
	MetaDistance m_distance;
	OverlapData m_overlap;
	RootFind m_rootFind;
};