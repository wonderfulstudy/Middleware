#include "stdafx.h"
#include "Insert.h"


Insert::Insert()
{
}


Insert::~Insert()
{
}

bool Insert::DirectExecute(SQLWCHAR * SQL)
{
	bool Rtn;
	//1.环境句柄
	Retcode = SQLAllocHandle(SQL_HANDLE_ENV, NULL, &Henv);
	Retcode = SQLSetEnvAttr(Henv, SQL_ATTR_ODBC_VERSION, (SQLPOINTER)SQL_OV_ODBC3, SQL_IS_INTEGER);
	//2.连接句柄
	Retcode = SQLAllocHandle(SQL_HANDLE_DBC, Henv, &Hdbc);
	Retcode = SQLConnect(Hdbc, (SQLWCHAR*)ServerName, sizeof(ServerName), (SQLWCHAR*)DataName, sizeof(DataName), (SQLWCHAR*)Password, sizeof(Password));

	if (Retcode == SQL_SUCCESS || Retcode == SQL_SUCCESS_WITH_INFO)
	{
		//方式一：直接执行
		/*
		1.分配一个语句句柄(statement handle)
		2.创建SQL语句
		3.执行语句
		4.销毁语句
		*/

		Retcode = SQLAllocHandle(SQL_HANDLE_STMT, Hdbc, &Hstmt);
		SQLExecDirect(Hstmt, SQL, SQLMAX);
		Rtn = true;
	}
	return Rtn;
}

bool Insert::BindingParameter(SQLWCHAR * SQL, Sensor Data)
{
	bool Rtn;
	//1.环境句柄
	Retcode = SQLAllocHandle(SQL_HANDLE_ENV, NULL, &Henv);
	Retcode = SQLSetEnvAttr(Henv, SQL_ATTR_ODBC_VERSION, (SQLPOINTER)SQL_OV_ODBC3, SQL_IS_INTEGER);
	//2.连接句柄
	Retcode = SQLAllocHandle(SQL_HANDLE_DBC, Henv, &Hdbc);
	Retcode = SQLConnect(Hdbc, (SQLWCHAR*)ServerName, sizeof(ServerName), (SQLWCHAR*)DataName, sizeof(DataName), (SQLWCHAR*)Password, sizeof(Password));
	if (Retcode == SQL_SUCCESS || Retcode == SQL_SUCCESS_WITH_INFO)
	{
		//方式二：绑定参数方式
		SQLINTEGER	P = SQL_NTS;
		Retcode = SQLAllocHandle(SQL_HANDLE_STMT, Hdbc, &Hstmt);
		//1.预编译
		Retcode = SQLPrepare(Hstmt, SQL, SQLMAX);//第三个参数与数组大小相同，而不是数据库列相同
		/*2.绑定参数*/
		Retcode = SQLBindParameter(Hstmt, 1, SQL_PARAM_INPUT, SQL_C_CHAR, SQL_CHAR, SQLCHAR, 0, &Data.gas_number, SQLCHAR, &P);
		Retcode = SQLBindParameter(Hstmt, 2, SQL_PARAM_INPUT, SQL_C_CHAR, SQL_VARCHAR, SQLVARCHAR, 0, &Data.gas_name, SQLVARCHAR, &P);
		Retcode = SQLBindParameter(Hstmt, 3, SQL_PARAM_INPUT, SQL_C_CHAR, SQL_VARCHAR, SQLVARCHAR, 0, &Data.time, SQLVARCHAR, &P);
		Retcode = SQLBindParameter(Hstmt, 4, SQL_PARAM_INPUT, SQL_C_CHAR, SQL_VARCHAR, SQLVARCHAR, 0, &Data.concentration, SQLVARCHAR, &P);
		Retcode = SQLBindParameter(Hstmt, 5, SQL_PARAM_INPUT, SQL_C_CHAR, SQL_CHAR, SQLCHAR, 0, &Data.sensor_number, SQLCHAR, &P);
		//3.执行
		Retcode = SQLExecute(Hstmt);
		if (Retcode == SQL_SUCCESS|| Retcode == SQL_SUCCESS_WITH_INFO)
		{
			Rtn = true;
		}
	}
	return Rtn;
}
