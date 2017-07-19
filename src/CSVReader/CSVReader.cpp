#include "CSVReader.h"
#include <fstream>
#include <iostream>
#include <sstream>
#include <cassert>
#include <algorithm>

CSVReader::CSVReader()
{
	data.clear();
}
CSVReader::CSVReader(const std::string& file)
{
	load(file);
}
CSVReader::~CSVReader()
{
	std::for_each(data.begin(), data.end(),
		[&](Row& row){row.clear(); Row().swap(row); });
	data.clear();
	Rows().swap(data);
}
void CSVReader::AllFunction(std::function<void(int row, int colum)> fun)
{
	for (int r = 0; r < rows();r++)
	{
		for (int c = 0; c < colums(); c++)
		{
			fun(r, c);
		}
	}
}
bool CSVReader::load(const std::string& filename)
{
	data.clear();
	std::ifstream file(filename);
	/* ファイルが読み込めなかったら */
	if (file.bad())
		return false;
	std::string line;
	while (std::getline(file, line))
	{
		std::stringstream stream(std::move(line));
		Row row;
		std::string val;
		/* カンマ区切りで読み込む */
		while (std::getline(stream, val, ','))
			row.push_back(val);
		row.shrink_to_fit();
		data.push_back(std::move(row));
	}
	data.shrink_to_fit();
	return true;
}
bool CSVReader::save(const std::string& filename)
{
	std::ofstream file(filename);
	/* ファイルが書き込めなかったら */
	if (file.bad())
		return false;
	for (int row = 0; row < rows(); ++row)
	{
		int col = 0;
		for (; col < colums(row) - 1; ++col)
		{
			file << get(row, col) << ",";
		}
		file << get(row, col) << "\n";
	}
	return true;
}
int CSVReader::rows() const
{
	return data.size();
}
int CSVReader::colums(unsigned int row) const
{
	if (rows() == 0)
		return 0;
	return data.at(row).size();
}
const std::string& CSVReader::get(unsigned int row, unsigned int col) const
{
	return data.at(row).at(col);
}
int CSVReader::geti(unsigned int row, unsigned int col) const
{
	return std::stoi(get(row, col));
}
float CSVReader::getf(unsigned int row, unsigned int col) const
{
	return std::stof(get(row, col));
}
double CSVReader::getd(unsigned int row, unsigned int col) const
{
	return std::stod(get(row, col));
}
long double CSVReader::getld(unsigned int row, unsigned int col) const
{
	return std::stold(get(row, col));
}
long CSVReader::getl(unsigned int row, unsigned int col) const
{
	return std::stol(get(row, col));
}
long long CSVReader::getll(unsigned int row, unsigned int col) const
{
	return std::stoll(get(row, col));
}