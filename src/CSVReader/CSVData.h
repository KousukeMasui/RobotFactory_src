#pragma once
#include<map>
#include"Math/Point2/Point2.h"
#include"Math/Vector/MyVector3.h"
#include"Math/Vector/MyVector2.h"
#include<functional>
#include<vector>
class CSVReader;
//CSVで得たデータを格納しておくクラス
//行ごとに違うオブジェクトのデータと決めて処理を行う
class CSVData 
{
public:
	enum class CSV_DATA_ID {
		UNIT_RADIUS=0,
		UNIT_HEIGHT,
		UNIT_ATTACK_RANGE,
		UNIT_LIFT_RANGE,
		

		UNIT_HP,
		UNIT_ATK,
		UNIT_SPD
	};
	//コンストラクタ
	CSVData();
	//デストラクタ
	~CSVData();
	//開始処理　csv読み込み
	void Start(const char* fileName);
	//終了処理　csv開放
	void End();

	//切り取り　vector3版
	void Set_V3(CSV_DATA_ID dataID, const Point2& start);
	//切り取り　vector3 終了位置付き
	void Set_V3(CSV_DATA_ID dataID, const Point2& start, const Point2& end);
	//vector2版
	void Set_V2(CSV_DATA_ID dataID, const Point2& start);
	//vector2版
	void Set_V2(CSV_DATA_ID dataID, const Point2& start, const Point2& end);
	//float版
	void Set_F(CSV_DATA_ID dataID, const Point2& start);
	//float版
	void Set_F(CSV_DATA_ID dataID, const Point2& start, int endRow);
	//文字列版
	void Set_Str(CSV_DATA_ID dataID, const Point2& start);
	//文字列版
	void Set_Str(CSV_DATA_ID dataID, const Point2& start, int endRow);

	//取得
	MyVector3 Get_V3(CSV_DATA_ID id,int row);
	std::vector<MyVector3> Gets_V3(CSV_DATA_ID id);
	MyVector2 Get_V2(CSV_DATA_ID id, int row);
	std::vector<MyVector2> Gets_V2(CSV_DATA_ID id);
	float Get_F(CSV_DATA_ID id, int row);
	std::vector<float> Gets_F(CSV_DATA_ID id);
	std::string Get_Str(CSV_DATA_ID id, int row);
	std::vector<std::string> Gets_Str(CSV_DATA_ID id);
private:
	void SetFunc(const Point2& start, const Point2& end, const std::function<void(int row, int startCol)>& func);

	template<typename DataClass>
	std::vector<DataClass> Gets(CSV_DATA_ID id, std::map<CSV_DATA_ID,std::map<int, DataClass>>& data)
	{
		std::vector<DataClass> result;

		for (auto itr = data[id].begin(); itr != data[id].end(); ++itr)
		{
			result.push_back(itr->second);
		}

		return result;
	}
private:
	//Vector2データ　dataID,row,データ
	std::map<CSV_DATA_ID, std::map<int, MyVector2>> m_v2Data;
	//Vector3データ　dataID,row,データ
	std::map<CSV_DATA_ID, std::map<int, MyVector3>> m_v3Data;
	//Vector3データ　dataID,row,データ
	std::map<CSV_DATA_ID, std::map<int, float>> m_fData;
	//Vector3データ　dataID,row,データ
	std::map<CSV_DATA_ID, std::map<int, std::string>> m_strData;
	CSVReader* m_csv;
};
