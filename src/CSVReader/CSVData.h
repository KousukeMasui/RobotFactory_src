#pragma once
#include<map>
#include"Math/Point2/Point2.h"
#include"Math/Vector/MyVector3.h"
#include"Math/Vector/MyVector2.h"
#include<functional>
#include<vector>
enum class CSV_DATA_ID {
	UNIT_RADIUS = 0,
	UNIT_HEIGHT,
	UNIT_ATTACK_RANGE,
	UNIT_LIFT_RANGE,


	UNIT_HP,
	UNIT_ATK,
	UNIT_SPD,

	PLAYER_COLOR,
	PLAYER_AMBIENT_COLOR,
	ENEMY_COLOR,
	ENEMY_AMBIENT_COLOR,

	UNIT_COLOR_CHANGE_INDICES,
	FACTORY_MAX_HP,					//工場の最大HP
	FACTORY_INIT_PARTS,				//工場が初期で持つ資源の数
	FACTORY_HEAL_INTERVAL_SECOND,	//工場の回復間隔
	FACTORY_INIT_UNIT_HP,			//ユニットの体力の初期レベル
	FACTORY_INIT_UNIT_ATK,			//ユニットの攻撃力の初期レベル
	FACTORY_INIT_UNIT_SPD,			//ユニットの速度の初期レベル
	FACTORY_INIT_HEAL_RANGE,		//工場の回復範囲の初期レベル
	FACTORY_INIT_HEAL_POWER,		//工場の回復力の初期レベル
	FACTORY_INIT_CREATE,			//ユニットの生成に必要な資源数
};

enum class DATA_TYPE {
	INT=0,
	FLOAT,
	STRING
};
class CSVReader;
//CSVで得たデータを格納しておくクラス
//行ごとに違うオブジェクトのデータと決めて処理を行う
class CSVData 
{
private:
	template<typename Type>
	class DataClass {
	public:
		DataClass(const std::function<Type(CSVReader* csv, int row, int col)>& getFunc):m_getFunc(getFunc) {};
		~DataClass() {};
		void Set(CSV_DATA_ID id, CSVReader* csv, const Point2& start,int endRow) {
			for (int r = start.y; r < endRow; r++) {
				m_data[id][r] = m_getFunc(csv, r, start.x);
			}
		}

		Type Get(CSV_DATA_ID id, int row) {
			return m_data[id][row];
		}
		std::vector<Type> Gets(CSV_DATA_ID id) {
			std::vector<Type> result;

			for (auto itr = m_data[id].begin(); itr != m_data[id].end(); ++itr)
			{
				result.push_back(itr->second);
			}

			return result;
		}
	private:
		std::map<CSV_DATA_ID, std::map<int, Type> > m_data;
		const std::function<Type(CSVReader* csv, int row, int col)> m_getFunc;
	};
public:
	//コンストラクタ
	CSVData();
	//デストラクタ
	~CSVData();
	//開始処理　csv読み込み
	void Start(const char* fileName);
	//終了処理　csv開放
	void End();


	void Set(DATA_TYPE type, CSV_DATA_ID dataID, const Point2& start);
	void Set(DATA_TYPE type, CSV_DATA_ID dataID, const Point2& start, int endRow);
	//取得
	float Get_F(CSV_DATA_ID id, int row);
	std::vector<float> Gets_F(CSV_DATA_ID id);
	std::string Get_Str(CSV_DATA_ID id, int row);
	std::vector<std::string> Gets_Str(CSV_DATA_ID id);
	int Get_I(CSV_DATA_ID id, int row);
	std::vector<int> Gets_I(CSV_DATA_ID id);
private:
	DataClass<int> m_intData;
	DataClass<float> m_floatData;
	DataClass<std::string> m_strData;
	CSVReader* m_csv;
};
