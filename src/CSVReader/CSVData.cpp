#include "CSVData.h"
#include"CSVReader.h"
CSVData::CSVData():
	m_csv(nullptr),
	m_intData([](CSVReader* csv, int row, int col) {return csv->geti(row, col); }),
	m_floatData([](CSVReader* csv, int row, int col) {return csv->getf(row, col); }),
	m_strData([](CSVReader* csv, int row, int col) {std::string s = csv->get(row, col); return s;  })
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

void CSVData::Set(DATA_TYPE type, CSV_DATA_ID dataID, const Point2 & start)
{
	Set(type, dataID, start, m_csv->rows());
}

void CSVData::Set(DATA_TYPE type, CSV_DATA_ID dataID, const Point2 & start, int endRow)
{
	switch (type)
	{
	case DATA_TYPE::INT:
		m_intData.Set(dataID, m_csv, start, endRow);
		break;
	case DATA_TYPE::FLOAT:
		m_floatData.Set(dataID, m_csv, start, endRow);
		break;
	case DATA_TYPE::STRING:
		m_strData.Set(dataID, m_csv, start, endRow);
		break;
	}
}

float CSVData::Get_F(CSV_DATA_ID id, int row)
{
	return m_floatData.Get(id, row);
}

std::vector<float> CSVData::Gets_F(CSV_DATA_ID id)
{
	return m_floatData.Gets(id);
}

std::string CSVData::Get_Str(CSV_DATA_ID id, int row)
{
	return m_strData.Get(id, row);
}

std::vector<std::string> CSVData::Gets_Str(CSV_DATA_ID id)
{
	return m_strData.Gets(id);
}

int CSVData::Get_I(CSV_DATA_ID id, int row)
{
	return m_intData.Get(id, row);
}

std::vector<int> CSVData::Gets_I(CSV_DATA_ID id)
{
	return m_intData.Gets(id);
}