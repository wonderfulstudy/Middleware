#pragma once
#include <windows.h>
#include <sql.h>
#include <sqlext.h>
#include <sqltypes.h>
#include <odbcss.h>
#include "Gas.h"
#include <string.h>

#define	ServerName	"ODBCServer"
#define	DataName	"sa"
#define Password	"123456"
#define SQLMAX		1000

class SqlInsert
{
public:
	SqlInsert();
	~SqlInsert();
	bool Excute(SQLCHAR *SQL);
	bool DirectExecute(Gas data);
};

