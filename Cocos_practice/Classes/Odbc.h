#pragma once
#include "sql.h"
#include "sqlext.h"
#include "definition.h"

class Odbc
{
public:
	static Odbc* _Inst;
	static Odbc* Odbc::GetInstance();

	bool			IsConnect(){ return _IsConnect; }

	bool			Connect(wchar_t* odbcName, wchar_t* mysqlId, wchar_t* password);
	void			Disonnect();

	int				GetUserId(std::string userName);
	std::string		GetPassword(std::string name);

	int				GetMapInfo(int map_id, SQLMapInfo info);
	std::string		GetRecentResult(int numToGet);
	std::string		GetTopPlayerList(int numToGet);

	bool			UpdatePlayerWinRate(int player_idnum);
	bool			UpdatePlayerRank(int player_idnum);

	bool			InsertData(std::string tableName, std::string colNames, std::string value);
	bool			CheckDataExist(std::string tableName, std::string colName, std::string value);
	std::string		SelectData(std::string tableName, std::string colNames, bool whereCon = false, std::string whereCol = "id", std::string value = "");
	bool			PushQuery(std::wstring query);
	
	void			ReadFileAndInsert(const char *path);
	void			CheckSuccess(int ret);
	std::string		GetMapData(int width, int height, int map_id);
	
	const char*		CreateCSV(const char* filename, int num);
		
	std::wstring	utf8_to_wstring(const std::string& str);
	std::string		wstring_to_utf8(const std::wstring& wstr);

private:
	Odbc();
	~Odbc();

	bool		_IsConnect = false;
	SQLHENV		_hEnv;
	SQLHDBC		_hDbc;
	SQLHSTMT	_hStmt;
};