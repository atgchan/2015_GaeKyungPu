#include "pch.h"
#include <Windows.h>
#include <iostream>
#include "Odbc.h"
#include <fstream>
#include <string>
#include <clocale>
#include <codecvt>

using namespace std;

Odbc* Odbc::_Inst = nullptr;

Odbc::Odbc()
	:_hEnv(nullptr), _hDbc(nullptr), _hStmt(nullptr)
{}

Odbc::~Odbc()
{
	_Inst = nullptr;
}

Odbc* Odbc::GetInstance()
{
	if (_Inst == nullptr)
		_Inst = new Odbc();
	else
		return _Inst;
}

bool Odbc::Connect(wchar_t* odbcName, wchar_t* mysqlId, wchar_t* password)
{
	int ret;

	ret = SQLAllocHandle(SQL_HANDLE_ENV, SQL_NULL_HANDLE, &_hEnv);
	ret = SQLSetEnvAttr(_hEnv, SQL_ATTR_ODBC_VERSION, (SQLPOINTER)SQL_OV_ODBC3, SQL_IS_INTEGER);
	ret = SQLAllocHandle(SQL_HANDLE_DBC, _hEnv, &_hDbc);

	ret = SQLConnect(
		_hDbc, 
		(SQLWCHAR*)odbcName, SQL_NTS,
		(SQLWCHAR*)mysqlId, SQL_NTS,
		(SQLWCHAR*)password, SQL_NTS
		);

	if (ret == SQL_SUCCESS || ret == SQL_SUCCESS_WITH_INFO)
	{
		_IsConnect = true;
		ret = SQLAllocHandle(SQL_HANDLE_STMT, _hDbc, &_hStmt);
		return true;
	}
	else
		return false;
}

void Odbc::Disonnect()
{
	if (_hStmt != nullptr)	
		SQLFreeHandle(SQL_HANDLE_STMT, _hStmt);
	if (_hDbc != nullptr)	
		SQLDisconnect(_hDbc);
	if (_hDbc != nullptr)	
		SQLFreeHandle(SQL_HANDLE_DBC, _hDbc);
	if (_hEnv != nullptr)	
		SQLFreeHandle(SQL_HANDLE_ENV, _hEnv);
	_IsConnect = false;
}

bool Odbc::PushQuery(std::wstring query)
{
	if (!_IsConnect || _Inst == nullptr)
		return false;

	SQLWCHAR* sql = (SQLWCHAR*)query.c_str();
	int ret = SQLExecDirect(_hStmt, sql, SQL_NTS);

	if (ret == SQL_SUCCESS)
		return true;
	else
		return false;
}

bool Odbc::InsertData(std::string tableName, std::string colNames, std::string values)
{
	if (!_IsConnect || _Inst == nullptr)
		return false;

	std::wstring query = L"INSERT INTO testudo.";
	query += utf8_to_wstring(tableName);
	query += L"(";
	query += utf8_to_wstring(colNames);
	query += L") VALUES(";
	query += utf8_to_wstring(values);
	query += L")";

	SQLWCHAR* sql = (SQLWCHAR*)query.c_str();

	int ret = SQLAllocHandle(SQL_HANDLE_STMT, _hDbc, &_hStmt);
	ret = SQLExecDirect(_hStmt, sql, SQL_NTS);

	if (ret == SQL_SUCCESS)
		return true;
	else
		return false;
}

int Odbc::GetUserId(std::string userName)
{
	if (!_IsConnect || _Inst == nullptr)
		return -1;

	std::wstring query = L"SELECT id FROM user WHERE name = '";
	query += utf8_to_wstring(userName);
	query += L"'";

	SQLWCHAR* sql = (SQLWCHAR*)query.c_str();

	int ret = SQLAllocHandle(SQL_HANDLE_STMT, _hDbc, &_hStmt);
	ret = SQLExecDirect(_hStmt, sql, SQL_NTS);
	//SQLBindCol(_hStmt, )

	if (ret == SQL_SUCCESS)
	{
		SQLLEN resultLen, idResult2;
		int idResult;

		while (TRUE)
		{
			if (ret == SQL_SUCCESS || ret == SQL_SUCCESS_WITH_INFO)
			{
				SQLGetData(_hStmt, 1, SQL_C_DEFAULT, &idResult, 1, &resultLen);
				SQLGetData(_hStmt, 1, SQL_C_LONG, &idResult, 1, &resultLen);
				SQLGetData(_hStmt, 1, SQL_C_ULONG, &idResult, 1, &resultLen);
				SQLGetData(_hStmt, 1, SQL_C_DEFAULT, &idResult2, 1, &resultLen);
				SQLGetData(_hStmt, 1, SQL_C_LONG, &idResult2, 1, &resultLen);
				SQLGetData(_hStmt, 1, SQL_C_ULONG, &idResult2, 1, &resultLen);
				return idResult;
			}
		}
	}
	else
		return -1;
}

std::string Odbc::GetPassword(std::string name)
{
	if (!_IsConnect || _Inst == nullptr)
		return "";

	std::wstring query = L"SELECT password FROM user WHERE name = '";
	query += utf8_to_wstring(name);
	query += L"'";
	
	SQLWCHAR* sql = (SQLWCHAR*)query.c_str();

	int ret = SQLAllocHandle(SQL_HANDLE_STMT, _hDbc, &_hStmt);
	ret = SQLExecDirect(_hStmt, sql, SQL_NTS);
	//SQLBindCol(_hStmt, )
	
	if (ret == SQL_SUCCESS)
	{
		SQLLEN resultLen;
		char strResult[32];

		while (TRUE)
		{
			ret = SQLFetch(_hStmt);
			if (ret == SQL_NO_DATA)
				return "[NO DATA]";

			if (ret == SQL_ERROR/* || ret == SQL_SUCCESS_WITH_INFO*/)
				return "An error occured\n";

			//			SELECT
			if (ret == SQL_SUCCESS || ret == SQL_SUCCESS_WITH_INFO)
			{
				SQLGetData(_hStmt, 1, SQL_C_CHAR, strResult, 32, &resultLen);
				return std::string(strResult);
			}
		}
	}
	else
		return "An error occured during excuting query!!";
}


std::string Odbc::SelectData(std::string tableName, std::string colNames, bool whereCon, std::string whereCol, std::string value)
{
	if (!_IsConnect || _Inst == nullptr)
		return "";

	std::wstring query = L"SELECT ";
	query += utf8_to_wstring(colNames);
	query += L" FROM ";
	query += utf8_to_wstring(tableName);
	
	if (whereCon)
	{
		query += L" WHERE ";
		query += utf8_to_wstring(whereCol);
		query += L" = '";
		query += utf8_to_wstring(value);
		query += L"'";
	}

	SQLWCHAR* sql = (SQLWCHAR*)query.c_str();
	int ret = SQLExecDirect(_hStmt, sql, SQL_NTS);

	if (ret == SQL_SUCCESS)
	{
		SQLLEN resultLen;
		char strResult[200];

		while (TRUE)
		{
			ret = SQLFetch(_hStmt);
			if (ret == SQL_NO_DATA)
				return "[NO DATA]";

			if (ret == SQL_ERROR || ret == SQL_SUCCESS_WITH_INFO)
				return "An error occured\n";

//			SELECT
			if (ret == SQL_SUCCESS || ret == SQL_SUCCESS_WITH_INFO)
			{
				SQLGetData(_hStmt, 1, SQL_C_WCHAR, strResult, 200, &resultLen);
				return std::string(strResult);
			}
		}
	}
	else
		return "An error occured during excuting query!!";
}

bool Odbc::CheckDataExist(std::string tableName, std::string colName, std::string value)
{
	if (!_IsConnect || _Inst == nullptr)
		return false;
	
	std::wstring query = L"SELECT ";
	query += utf8_to_wstring(colName);
	query += L" FROM ";
	query += utf8_to_wstring(tableName);
	query += L" WHERE ";
	query += utf8_to_wstring(colName);
	query += L" = '";
	query += utf8_to_wstring(value);
	query += L"'";

	SQLWCHAR* sql = (SQLWCHAR*)query.c_str();
	int ret = SQLExecDirect(_hStmt, sql, SQL_NTS);

	if (ret == SQL_SUCCESS)
	{
		ret = SQLFetch(_hStmt);
		if (ret == SQL_NO_DATA)
			return false;

		if (ret == SQL_ERROR || ret == SQL_SUCCESS_WITH_INFO)
			return false;

		return true;
	}
	else
		return false;
}


void Odbc::CheckSuccess(int ret)
{
	if (ret == SQL_SUCCESS)
	{
		ret = SQLFetch(_hStmt);
		if (ret == SQL_NO_DATA)
		{
			cout << "[NO DATA]" << endl;
			return;
		}
		if (ret == SQL_ERROR || ret == SQL_SUCCESS_WITH_INFO)
			printf("An error occured\n");
	}
	else
		cout << "An error occured during excuting query!!" << endl;

}

void Odbc::ReadFileAndInsert(const char *path)
{
	cout << "[Read File And Insert]" << endl;

	wifstream file(path);
	if (!file.is_open())
	{
		printf("[NO FILE]\n");
		return;
	}
	wstring buffer;

	getline(file, buffer);

	wchar_t* context;

	while (getline(file, buffer))
	{
		wstring query = L"INSERT INTO millibook (id, title, author, publication, pub_year, isbn, price) VALUES (";
		wcout << buffer << endl;

		wchar_t* part = wcstok_s(const_cast<wchar_t*>(buffer.c_str()), L",", &context);

		int index = 0;
		wstring array[7];

		while (part != NULL) {
			int len = wcslen(part);

			if (part[len - 1] == L' ')
				part[len - 1] = L'\0';

			array[index] = std::wstring(part);
			while (array[index][0] == L'\"')
			{
				part = wcstok_s(NULL, L",", &context);
				int len = wcslen(part);

				while (part[len - 1] == L' ')
				{
					part[len - 1] = L'\0';
					len = wcslen(part);
				}

				if (part[len - 1] == L'\"')
				{
					part[len - 1] = L'\0';
					array[index] += std::wstring(part);
					for (int i = 0; i < wcslen(array[index].c_str()); ++i)
					{
						array[index][i] = array[index][i + 1];
					}
					break;
				}
				array[index] += std::wstring(part);

			}
			part = wcstok_s(NULL, L",", &context);
			index++;
		}

		for (int i = 0; i < 7; ++i)
		{
			if ((i == 1) || (i == 2) || (i == 3) || (i == 5))
				array[i] = L"'" + array[i] + L"'";
			query += array[i];
			if (i != 6)
				query += L",";
		}
		query += L")";

		wcout << query << endl;

		SQLWCHAR* sql = (SQLWCHAR*)query.c_str();
		int ret = SQLExecDirect(_hStmt, sql, SQL_NTS);

		if (ret == SQL_SUCCESS)
			cout << "success" << endl;
		else
			cout << "An error occured during excuting query!!\n" << endl;
	}
	file.close();

}

void Odbc::SelectBookData()
{
	cout << "[Select Book Data]" << endl;

	int ret = SQLExecDirect(_hStmt, (SQLWCHAR*)L"SELECT author, title, price FROM test.book", SQL_NTS);

	if (ret == SQL_SUCCESS)
	{
		int iCount = 0;
		SQLLEN iAuthorLen, iTitleLen, iPriceLen, iPrice;
		char strAuthor[200], strTitle[200];

		while (TRUE)
		{
			ret = SQLFetch(_hStmt);
			if (ret == SQL_NO_DATA)
			{
				cout << "[NO DATA]" << endl;
				break;
			}
			if (ret == SQL_ERROR || ret == SQL_SUCCESS_WITH_INFO)
				printf("An error occured\n");

			//			SELECT
			if (ret == SQL_SUCCESS || ret == SQL_SUCCESS_WITH_INFO)
			{
				SQLGetData(_hStmt, 1, SQL_C_WCHAR, strAuthor, 200, &iAuthorLen);
				SQLGetData(_hStmt, 2, SQL_C_WCHAR, strTitle, 200, &iTitleLen);
				SQLGetData(_hStmt, 3, SQL_C_ULONG, &iPrice, 0, &iPriceLen);

				cout << "Row : " << iCount++ << endl;
				cout << strAuthor << " " << strTitle << " " << iPrice << endl;
			}
		}
	}
	else
		cout << "An error occured during excuting query!!" << endl;
}

const char* Odbc::CreateCSV(const char* filename, int num)
{
	cout << "[ CREATE CSV ]" << endl;

	//const char* filename = "millibook.csv";
	ofstream of(filename);

	if (of.bad())
	{
		cout << "ERROR" << endl;
		return NULL;
	}

	for (int i = 1; i < num; ++i)
	{
		int ranNum = rand() % 1000;

		std::string line = "";
		line += to_string(i);
		line += ",title";
		line += to_string(i);
		line += ",author";
		line += to_string(ranNum);
		line += "\n";

		of << line;

		if (i % 50000 == 0)
			cout << "[ CREATE LINE " << i << " ]" << endl;
	}
	of.close();
	cout << "[ COMPLETE ] " << endl;
	return filename;
}

std::wstring Odbc::utf8_to_wstring(const std::string& str)
{
	std::wstring_convert<std::codecvt_utf8<wchar_t>> myconv;
	return myconv.from_bytes(str);
}

std::string Odbc::wstring_to_utf8(const std::wstring& str)
{
	std::wstring_convert<std::codecvt_utf8<wchar_t>> myconv;
	return myconv.to_bytes(str);
}