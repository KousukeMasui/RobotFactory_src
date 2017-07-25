#include "CSVData.h"
#include"CSVReader.h"
CSVData::CSVData():
	m_csv(nullptr)
{
}

CSVData::~CSVData()
{
	if(m_csv != nullptr)delete m_csv;
}

void CSVData::Start(const char * fileName)
{
	m_csv = new CSVReader(fileName);
}

void CSVData::End()
{
	if (m_csv != nullptr)delete m_csv;
	m_csv = nullptr;
}

//切り取り　vector3版
void CSVData::Set_V3(CSV_DATA_ID dataID, const Point2 & start) {
	Set_V3(dataID, start, Point2(m_csv->colums(), m_csv->rows()));
}

//切り取り　vector3 終了位置付き
void CSVData::Set_V3(CSV_DATA_ID dataID, const Point2 & start, const Point2 & end){
	SetFunc(start, end, [&](int row, int startCol) {
		m_v3Data[dataID][row] = MyVector3(m_csv->getf(row, startCol + 0), m_csv->getf(row, startCol + 1), m_csv->getf(row, startCol + 2));
	});
}

void CSVData::Set_V2(CSV_DATA_ID dataID, const Point2 & start)
{
	Set_V2(dataID, start, Point2(m_csv->colums(), m_csv->rows()));
}

void CSVData::Set_V2(CSV_DATA_ID dataID, const Point2 & start, const Point2 & end)
{
	SetFunc(start, end, [&](int row, int startCol) {
		m_v2Data[dataID][row] = MyVector2(m_csv->getf(row, startCol + 0), m_csv->getf(row, startCol + 1));
	});
}

void CSVData::Set_F(CSV_DATA_ID dataID, const Point2 & start)
{
	Set_F(dataID, start,m_csv->rows());
}

void CSVData::Set_F(CSV_DATA_ID dataID, const Point2 & start, int endRow)
{
	SetFunc(start, Point2(start.x,endRow), [&](int row, int startCol) {
		m_fData[dataID][row] = m_csv->getf(row, startCol);
	});
}

void CSVData::Set_Str(CSV_DATA_ID dataID, const Point2 & start)
{
	Set_Str(dataID, start, m_csv->rows());
}

void CSVData::Set_Str(CSV_DATA_ID dataID, const Point2 & start, int endRow)
{
	SetFunc(start, Point2(start.x, endRow), [&](int row, int startCol) {
		m_strData[dataID][row] = m_csv->get(row, startCol);
	});
}

MyVector3 CSVData::Get_V3(CSV_DATA_ID id, int row)
{
	return m_v3Data[id][row];
}

std::vector<MyVector3> CSVData::Gets_V3(CSV_DATA_ID id)
{
	return Gets<MyVector3>(id, m_v3Data);
}

MyVector2 CSVData::Get_V2(CSV_DATA_ID id, int row)
{
	return m_v2Data[id][row];
}

std::vector<MyVector2> CSVData::Gets_V2(CSV_DATA_ID id)
{
	return Gets<MyVector2>(id, m_v2Data);
}

float CSVData::Get_F(CSV_DATA_ID id, int row)
{
	return m_fData[id][row];
}

std::vector<float> CSVData::Gets_F(CSV_DATA_ID id)
{
	return Gets<float>(id, m_fData);
}

std::string CSVData::Get_Str(CSV_DATA_ID id, int row)
{
	return m_strData[id][row];
}

std::vector<std::string> CSVData::Gets_Str(CSV_DATA_ID id)
{
	return Gets<std::string>(id, m_strData);
}


void CSVData::SetFunc(const Point2 & start, const Point2 & end, const std::function<void(int row, int startCol)>& func) {
	for (int r = start.y; r < end.y; r++)
	{
		func(r, start.x);
	}
}
