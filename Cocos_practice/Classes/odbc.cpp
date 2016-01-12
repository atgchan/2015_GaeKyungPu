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

	if (_IsConnect)
		return true;

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

std::string Odbc::GetUserInfo(int userid)
{
	if (!_IsConnect || _Inst == nullptr)
		return "CONNECT ERROR";

	std::wstring query = L"SELECT name, total_play, winRate, grade FROM user WHERE id = ";
	query += std::to_wstring(userid);

	SQLWCHAR* sql = (SQLWCHAR*)query.c_str();
	int ret = SQLAllocHandle(SQL_HANDLE_STMT, _hDbc, &_hStmt);
	ret = SQLExecDirect(_hStmt, sql, SQL_NTS);

	if (ret == SQL_SUCCESS)
	{
		SQLLEN resultLen;
		char strName[32], strRateing[32];
		int totalPlay;
		float winRate;

		ret = SQLFetch(_hStmt);
		if (ret == SQL_SUCCESS)
		{
			SQLGetData(_hStmt, 1, SQL_C_CHAR, strName, 32, &resultLen);
			SQLGetData(_hStmt, 2, SQL_C_DEFAULT, &totalPlay, 0, &resultLen);
			SQLGetData(_hStmt, 3, SQL_C_FLOAT, &winRate, 0, &resultLen);
			SQLGetData(_hStmt, 4, SQL_C_CHAR, strRateing, 32, &resultLen);

			std::string result = std::string(strName);
			result += ", ";
			result += std::to_string(totalPlay);
			result += ", ";
			result += std::to_string(winRate);
			result += ", ";
			result += std::string(strRateing);
			result += "\n";

			return result;
		}
	}
	else
		return "NO DATA";
}

bool Odbc::UpdatePlayerPassword( int userid, std::string newPw)
{
	if (!_IsConnect || _Inst == nullptr)
		return false;

	std::wstring query = L"UPDATE user SET password = '";
	query += utf8_to_wstring(newPw);
	query += L"' WHERE id = ";
	query += std::to_wstring(userid);

	SQLWCHAR* sql = (SQLWCHAR*)query.c_str();
	int ret = SQLAllocHandle(SQL_HANDLE_STMT, _hDbc, &_hStmt);
	ret = SQLExecDirect(_hStmt, sql, SQL_NTS);

	if (ret == SQL_SUCCESS)
		return true;
	
	else
		return false;
}

std::string Odbc::GetRecentResult(int numToGet)
{
	if (!_IsConnect || _Inst == nullptr)
		return false;

	std::wstring query = L"call getRecentResult(";
	query += std::to_wstring(numToGet);
	query += L")";

	SQLWCHAR* sql = (SQLWCHAR*)query.c_str();
	int ret = SQLAllocHandle(SQL_HANDLE_STMT, _hDbc, &_hStmt);
	ret = SQLExecDirect(_hStmt, sql, SQL_NTS);

	if (ret == SQL_SUCCESS)
	{
		SQLLEN resultLen;
		wchar_t wstrWinner[32];
		char strWinner[32], strLoser[32], mapName[32];
		int totalTurn;

		std::string result = "";

		while (TRUE)
		{
			ret = SQLFetch(_hStmt);
			if (ret == SQL_SUCCESS)
			{
				//SQLGetData(_hStmt, 2, SQL_C_WCHAR, wstrWinner, 32, &resultLen);
				SQLGetData(_hStmt, 2, SQL_C_CHAR, strWinner, 32, &resultLen);
				SQLGetData(_hStmt, 3, SQL_C_CHAR, strLoser, 32, &resultLen);
				SQLGetData(_hStmt, 4, SQL_C_CHAR, mapName, 32, &resultLen);
				SQLGetData(_hStmt, 5, SQL_C_DEFAULT, &totalTurn, 0, &resultLen);

				/*
				std::wstring temp = wstring(wstrWinner);
				std::string strWinner = "";
				strWinner.assign(temp.begin(), temp.end());
				*/

				//result += strWinner;
				result += std::string(strWinner);
				result += " ";
				result += std::string(strLoser);
				result += " ";
				result += std::string(mapName);
				result += " ";
				result += std::to_string(totalTurn);
				result += "\n";
			}
			else
				break;
		}
		return result;
	}
	else
		return false;
}

std::string Odbc::GetResultByTurn(int numToGet)
{
	if (!_IsConnect || _Inst == nullptr)
		return false;

	std::wstring query = L"call getResultByTurn(";
	query += std::to_wstring(numToGet);
	query += L")";

	SQLWCHAR* sql = (SQLWCHAR*)query.c_str();
	int ret = SQLAllocHandle(SQL_HANDLE_STMT, _hDbc, &_hStmt);
	ret = SQLExecDirect(_hStmt, sql, SQL_NTS);

	if (ret == SQL_SUCCESS)
	{
		SQLLEN resultLen;
		wchar_t wstrWinner[32];
		char strWinner[32], strLoser[32], mapName[32];
		int totalTurn;

		std::string result = "";

		while (TRUE)
		{
			ret = SQLFetch(_hStmt);
			if (ret == SQL_SUCCESS)
			{
				//SQLGetData(_hStmt, 2, SQL_C_WCHAR, wstrWinner, 32, &resultLen);
				SQLGetData(_hStmt, 2, SQL_C_CHAR, strWinner, 32, &resultLen);
				SQLGetData(_hStmt, 3, SQL_C_CHAR, strLoser, 32, &resultLen);
				SQLGetData(_hStmt, 4, SQL_C_CHAR, mapName, 32, &resultLen);
				SQLGetData(_hStmt, 5, SQL_C_DEFAULT, &totalTurn, 0, &resultLen);

				/*
				std::wstring temp = wstring(wstrWinner);
				std::string strWinner = "";
				strWinner.assign(temp.begin(), temp.end());
				*/

				//result += strWinner;
				result += std::string(strWinner);
				result += " ";
				result += std::string(strLoser);
				result += " ";
				result += std::string(mapName);
				result += " ";
				result += std::to_string(totalTurn);
				result += "\n";
			}
			else
				break;
		}
		return result;
	}
	else
		return false;
}

std::string Odbc::GetTopPlayerList(int numToGet)
{
	if (!_IsConnect || _Inst == nullptr)
		return false;

	std::wstring query = L"SELECT name, total_play, winRate, grade FROM testudo.user ORDER BY winRate DESC, total_play DESC LIMIT ";
	query += std::to_wstring(numToGet);

	SQLWCHAR* sql = (SQLWCHAR*)query.c_str();
	int ret = SQLAllocHandle(SQL_HANDLE_STMT, _hDbc, &_hStmt);
	ret = SQLExecDirect(_hStmt, sql, SQL_NTS);

	if (ret == SQL_SUCCESS)
	{
		SQLLEN resultLen;
		wchar_t wstrName[32];
		char strName[32], strRating[32];
		int total_play;
		float winRate;

		std::string result = "";

		while (TRUE)
		{
			ret = SQLFetch(_hStmt);
			if (ret == SQL_SUCCESS)
			{
				//SQLGetData(_hStmt, 1, SQL_C_WCHAR, wstrName, 32, &resultLen);
				SQLGetData(_hStmt, 1, SQL_C_CHAR, strName, 32, &resultLen);
				SQLGetData(_hStmt, 2, SQL_C_DEFAULT, &total_play, 0, &resultLen);
				SQLGetData(_hStmt, 3, SQL_C_FLOAT, &winRate, 0, &resultLen);
				SQLGetData(_hStmt, 4, SQL_C_CHAR, strRating, 32, &resultLen);

				//std::wstring temp = wstring(wstrName);
				//std::string strName(temp.begin(), temp.end());

				result += std::string(strRating);
				result += " ";
				result += std::string(strName);
				result += " ";
				result += std::to_string(total_play);
				result += " ";
				result += std::to_string(winRate);
				result += "\n";
			}
			else
				break;
		}
		return result;
	}
	else
		return false;
}

bool Odbc::UpdatePlayerWinRate(int player_idnum)
{
	if (!_IsConnect || _Inst == nullptr)
		return false;

	std::wstring query = L"call updatePlayerWinRate(";
	query += std::to_wstring(player_idnum);
	query += L")";

	SQLWCHAR* sql = (SQLWCHAR*)query.c_str();
	int ret = SQLAllocHandle(SQL_HANDLE_STMT, _hDbc, &_hStmt);
	ret = SQLExecDirect(_hStmt, sql, SQL_NTS);

	if (ret == SQL_SUCCESS)
		return true;
	else
		return false;
}

bool Odbc::UpdatePlayerRank(int player_idnum)
{
	if (!_IsConnect || _Inst == nullptr)
		return false;

	std::wstring query = L"call updateUserRank(";
	query += std::to_wstring(player_idnum);
	query += L")";

	SQLWCHAR* sql = (SQLWCHAR*)query.c_str();
	int ret = SQLAllocHandle(SQL_HANDLE_STMT, _hDbc, &_hStmt);
	ret = SQLExecDirect(_hStmt, sql, SQL_NTS);

	if (ret == SQL_SUCCESS)
		return true;
	else
		return false;
}

int Odbc::GetMapInfo(int map_id, SQLMapInfo info)
{
	if (!_IsConnect || _Inst == nullptr)
		return -1;

	std::wstring query = L"SELECT map_id, map_name, max_width, max_height FROM map_list WHERE map_id = ";
	query += std::to_wstring(map_id);

	SQLWCHAR* sql = (SQLWCHAR*)query.c_str();
	int ret = SQLAllocHandle(SQL_HANDLE_STMT, _hDbc, &_hStmt);
	ret = SQLExecDirect(_hStmt, sql, SQL_NTS);

	if (ret == SQL_SUCCESS)
	{
		ret = SQLFetch(_hStmt);

		SQLLEN resultLen;
		int infoResult;
		
		SQLGetData(_hStmt, info, SQL_C_DEFAULT, &infoResult, 0, &resultLen);
		return infoResult;
	}
	else
		return -1;
}

std::string	Odbc::GetMapData(int width, int height, int map_id)
{
	if (!_IsConnect || _Inst == nullptr)
		return "";

	std::wstring query = L"SELECT tile_type FROM map_data WHERE pos_x = ";
	query += std::to_wstring(width);
	query += L" AND pos_y = ";
	query += std::to_wstring(height);
	query += L" AND map_id = ";
	query += std::to_wstring(map_id);

	SQLWCHAR* sql = (SQLWCHAR*)query.c_str();
	int ret = SQLAllocHandle(SQL_HANDLE_STMT, _hDbc, &_hStmt);
	ret = SQLExecDirect(_hStmt, sql, SQL_NTS);

	if (ret == SQL_SUCCESS)
	{
		SQLLEN resultLen;
		char strResult[200];

		ret = SQLFetch(_hStmt);
		SQLGetData(_hStmt, 1, SQL_C_CHAR, strResult, 200, &resultLen);
	
		return std::string(strResult);
	}
	else
		return "TILE_NULL";
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

	if (ret == SQL_SUCCESS)
	{
		SQLLEN resultLen, idResult2;
		int idResult;

		ret = SQLFetch(_hStmt);
		if (ret == SQL_NO_DATA)
			return -1;
		
		if (ret == SQL_ERROR || ret == SQL_SUCCESS_WITH_INFO)
			return -1;

		if (ret == SQL_SUCCESS)
		{
			SQLGetData(_hStmt, 1, SQL_C_DEFAULT, &idResult, 0, &resultLen);
			return idResult;
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
	
	if (ret == SQL_SUCCESS)
	{
		SQLLEN resultLen;
		char strResult[32];

		while (TRUE)
		{
			ret = SQLFetch(_hStmt);
			if (ret == SQL_NO_DATA)
				return "[NO DATA]";

			if (ret == SQL_ERROR || ret == SQL_SUCCESS_WITH_INFO)
				return "An error occured\n";

			if (ret == SQL_SUCCESS)
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

			if (ret == SQL_SUCCESS)
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
	int ret = SQLAllocHandle(SQL_HANDLE_STMT, _hDbc, &_hStmt);
	ret = SQLExecDirect(_hStmt, sql, SQL_NTS);

	if (ret == SQL_SUCCESS)
	{
		ret = SQLFetch(_hStmt);
		if (ret == SQL_NO_DATA || ret == SQL_ERROR || ret == SQL_SUCCESS_WITH_INFO)
			return false;

		return true;
	}
	else
		return false;
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