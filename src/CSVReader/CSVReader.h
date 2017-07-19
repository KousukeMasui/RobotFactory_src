
#ifndef _CSV_READER_H_
#define _CSV_READER_H_

#include <string>
#include <vector>
#include<functional>
class CSVReader
{
public :
	CSVReader();
	explicit CSVReader(const std::string& file);
	~CSVReader();
	//�S�Ă����[�v������	������function�ōs�������������s��
	void AllFunction(std::function<void(int row,int colum)> fun);
	/**********
	*	@brief �ǂݍ���
	*	@param[in] filename [std::string]
	*	@note -
	*
	*	@return	�ǂݍ��݂ɐ���������^
	**********/
	bool load(const std::string& filename);
	/**********
	*	@brief ���݂̓ǂݍ��܂�Ă���l�̕ۑ�
	*	@param[in] filename [std::string]
	*	@note -
	*
	*	@return	�ۑ��ɐ���������^
	**********/
	bool save(const std::string& filename);
	/**********
	*	@brief �s���擾
	*	@note �\�Ō����c
	*
	*	@return	�s����Ԃ�
	**********/
	int rows() const;
	/**********
	*	@brief �񐔎擾
	*	@param[in] row [unsigned int] default = 0
	*	@note �\�Ō�����, �s���Ȃ�������O���Ԃ�
	*
	*	@return	�񐔂�Ԃ�
	**********/
	int colums(unsigned int row = 0) const;
	/**********
	*	@brief ������擾
	*	@param[in]	row [unsigned int]
	*	@param[in]	col [unsigned int]
	*	@note -
	*
	*	@return	�ǂݍ��܂�Ă��镶�����Ԃ�
	**********/
	const std::string& get(unsigned int row, unsigned int col) const;
	/**********
	*	@brief ���l�擾int
	*	@param[in]	row [unsigned int]
	*	@param[in]	col [unsigned int]
	*	@note -
	*
	*	@return	�������int�^�ɕϊ��������̂�Ԃ�
	**********/
	int geti(unsigned int row, unsigned int col) const;
	/**********
	*	@brief ���l�擾float
	*	@param[in]	row [unsigned int]
	*	@param[in]	col [unsigned int]
	*	@note -
	*
	*	@return	�������float�^�ɕϊ��������̂�Ԃ�
	**********/
	float getf(unsigned int row, unsigned int col) const;
	/**********
	*	@brief ���l�擾double
	*	@param[in]	row [unsigned int]
	*	@param[in]	col [unsigned int]
	*	@note -
	*
	*	@return	�������double�^�ɕϊ����ꂽ���̂�Ԃ�
	**********/
	double getd(unsigned int row, unsigned int col) const;
	/**********
	*	@brief ���l�擾long double
	*	@param[in]	row [unsigned int]
	*	@param[in]	col [unsigned int]
	*	@note -
	*
	*	@return	�������long double�^�ɕϊ����ꂽ���̂�Ԃ�
	**********/
	long double getld(unsigned int row, unsigned int col) const;
	/**********
	*	@brief ���l�擾long
	*	@param[in]	row [unsigned int]
	*	@param[in]	col [unsigned int]
	*	@note -
	*
	*	@return	�������long�^�ɕϊ����ꂽ���̂�Ԃ�
	**********/
	long getl(unsigned int row, unsigned int col) const;
	/**********
	*	@brief ���l�擾long long
	*	@param[in]	row [unsigned int]
	*	@param[in]	col [unsigned int]
	*	@note -
	*
	*	@return	�������long long�^�ɕϊ����ꂽ���̂�Ԃ�
	**********/
	long long getll(unsigned int row, unsigned int col) const;

private :	/* Copy Guard */
	CSVReader(const CSVReader& other);
	CSVReader& operator = (const CSVReader& other);

private :
	typedef std::vector<std::string> Row;
	typedef std::vector<Row> Rows;
	Rows data;
};

#endif