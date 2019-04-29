#include "stdafx.h"
#include "SqlInsert.h"


SqlInsert::SqlInsert()
{
}


SqlInsert::~SqlInsert()
{
}

bool SqlInsert::Excute(SQLCHAR * SQL)
{
	bool Rtn = false;
	SQLHENV		Henv;
	SQLHDBC		Hdbc;
	SQLHSTMT	Hstmt;
	SQLRETURN	Retcode;

	//1.环境句柄
	Retcode = SQLAllocHandle(SQL_HANDLE_ENV, NULL, &Henv);
	Retcode = SQLSetEnvAttr(Henv, SQL_ATTR_ODBC_VERSION, (SQLPOINTER)SQL_OV_ODBC3, SQL_IS_INTEGER);
	//2.连接句柄
	Retcode = SQLAllocHandle(SQL_HANDLE_DBC, Henv, &Hdbc);
	Retcode = SQLConnect(Hdbc, (SQLCHAR*)ServerName, SQL_NTS, (SQLCHAR*)DataName, SQL_NTS, (SQLCHAR*)Password, SQL_NTS);

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
		Retcode = SQLExecDirect(Hstmt, SQL, SQLMAX);

		SQLCloseCursor(Hstmt);
		SQLFreeHandle(SQL_HANDLE_STMT, Hstmt);
		Rtn = true;
	}
	SQLDisconnect(Hdbc);
	SQLFreeHandle(SQL_HANDLE_DBC, Hdbc);
	SQLFreeHandle(SQL_HANDLE_ENV, Henv);

	return Rtn;
}

bool SqlInsert::DirectExecute(Gas data)
{
	bool Rtn = false;
	SQLHENV		Henv;
	SQLHDBC		Hdbc;
	SQLHSTMT	Hstmt;
	SQLRETURN	Retcode;

	char sql[60] = "\0";
	char sql1[] = "insert into 气体数据 values('";
	char sql2[] = "','";
	char sql3[] = "')";

	strcat_s(sql, sizeof(sql), sql1);
	strcat_s(sql, sizeof(sql), data.gas_number);
	strcat_s(sql, sizeof(sql), sql2);
	strcat_s(sql, sizeof(sql), data.gas_name);
	strcat_s(sql, sizeof(sql), sql2);
	strcat_s(sql, sizeof(sql), data.time);
	strcat_s(sql, sizeof(sql), sql2);
	strcat_s(sql, sizeof(sql), data.concentration);
	strcat_s(sql, sizeof(sql), sql2);
	strcat_s(sql, sizeof(sql), data.sensor_number);
	strcat_s(sql, sizeof(sql), sql3);

	//1.环境句柄
	Retcode = SQLAllocHandle(SQL_HANDLE_ENV, NULL, &Henv);
	Retcode = SQLSetEnvAttr(Henv, SQL_ATTR_ODBC_VERSION, (SQLPOINTER)SQL_OV_ODBC3, SQL_IS_INTEGER);
	//2.连接句柄
	Retcode = SQLAllocHandle(SQL_HANDLE_DBC, Henv, &Hdbc);
	Retcode = SQLConnect(Hdbc, (SQLCHAR*)ServerName, SQL_NTS, (SQLCHAR*)DataName, SQL_NTS, (SQLCHAR*)Password, SQL_NTS);

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
		Retcode = SQLExecDirect(Hstmt, (SQLCHAR*)sql, 60);

		SQLCloseCursor(Hstmt);
		SQLFreeHandle(SQL_HANDLE_STMT, Hstmt);
		Rtn = true;
	}
	SQLDisconnect(Hdbc);
	SQLFreeHandle(SQL_HANDLE_DBC, Hdbc);
	SQLFreeHandle(SQL_HANDLE_ENV, Henv);

	return Rtn;
}
