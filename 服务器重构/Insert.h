#pragma once
#include <windows.h>
#include <sql.h>
#include <sqlext.h>
#include <sqltypes.h>
#include <odbcss.h>
#include "Sensor.h"

#define	ServerName	"ODBCServer"
#define	DataName	"sa"
#define Password	"12345678"
#define SQLMAX		1000

#define SQLCHAR		4
#define	SQLVARCHAR	50

class Insert
{
public:
	Insert();
	~Insert();
	bool DirectExecute(SQLWCHAR *SQL);
	bool BindingParameter(SQLWCHAR *SQL, Sensor Data);
private:
	SQLHENV		Henv;
	SQLHDBC		Hdbc;
	SQLHSTMT	Hstmt;
	SQLRETURN	Retcode;
};

