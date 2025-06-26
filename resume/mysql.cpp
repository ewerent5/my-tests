#include <mysql.h>

using namespace std;

int main() {
	MYSQL mysql;
	MYSQL_RES* res;
	MYSQL_ROW row;

	int i = 0;

	// �������� ���������� ����������
	mysql_init(&mysql);
	if (&mysql == nullptr) {
		// ���� ���������� �� ������� � ������� ��������� �� ������
		cout << "Error: can't create MySQL-descriptor" << endl;
	}

	// ������������ � �������
	if (!mysql_real_connect(&mysql, "localhost", "root", "root", "testdb", NULL, NULL, 0)) {
		// ���� ��� ����������� ���������� ���������� � �� ������� ��������� �� ������
		cout << "Error: can't connect to database " << mysql_error(&mysql) << endl;
	}
	else {
		// ���� ���������� ������� ����������� ������� ����� � "Success!"
		cout << "Success!" << endl;
	}

	mysql_set_character_set(&mysql, "utf8");
	//������� ���������� �� ��������� �� ������, �� ��������� ��� latin1
	cout << "connection characterset: " << mysql_character_set_name(&mysql) << endl;

	mysql_query(&mysql, "SELECT * FROM test"); //������ ������ � �������

	//������� ��� ��� ���� � ���� ����� ����
	if (res = mysql_store_result(&mysql)) {
		while (row = mysql_fetch_row(res)) {
			for (i = 0; i < mysql_num_fields(res); i++) {
				cout << row[i] << "  ";
			}
			cout << endl;
		}
	}
	else
		cout << "������ MySql ����� " << mysql_error(&mysql);

	// ��������� ���������� � �������� ���� ������
	mysql_close(&mysql);

	system("Pause");

	return 0;
}

/*
mysql_set_character_set()	������������� ����� �������� ��� ���� ������
mysql_query()	��������� SQL-������, �������� � ���� ������ � ������� �������� � �����
mysql_store_result()	��������� ������ �������������� ����� ��� ���������� ������� mysql_query()
mysql_fetch_row()	��������� ��������� ������ �� ��������������� ������
mysql_num_fields()	���������� ���������� �������� � �������������� ������
*/



#include <iostream>
#include <windows.h>
#include <sqlext.h>
#include <sqltypes.h>
#include <sql.h>

using namespace std;


int main() {

    constexpr auto SQL_RESULT_LEN = 240;
    constexpr auto SQL_RETURN_CODE_LEN = 1024;

    SQLHANDLE sqlConnHandle{ nullptr }; // ���������� ��� ���������� � ����� ������
    SQLHANDLE sqlEnvHandle{ nullptr }; // ���������� ��������� ���� ������
    SQLHANDLE sqlStmtHandle{ nullptr };  // ���������� ��� ���������� �������� � ���� ������
    SQLWCHAR retconstring[SQL_RETURN_CODE_LEN]{}; // ������ ��� ���� �������� �� ������� API ODBC


    // �������� ���������� ��� ���� ������
    if (SQL_SUCCESS != SQLAllocHandle(SQL_HANDLE_ENV, SQL_NULL_HANDLE, &sqlEnvHandle))
        goto COMPLETED;

    if (SQL_SUCCESS != SQLSetEnvAttr(sqlEnvHandle, SQL_ATTR_ODBC_VERSION, (SQLPOINTER)SQL_OV_ODBC3, 0))
        goto COMPLETED;

    if (SQL_SUCCESS != SQLAllocHandle(SQL_HANDLE_DBC, sqlEnvHandle, &sqlConnHandle))
        goto COMPLETED;

    cout << "Attempting connection to SQL Server...\n";

    // ������������� ���������� � ��������  
    switch (SQLDriverConnect(sqlConnHandle,
        GetDesktopWindow(),
        (SQLWCHAR*)L"DRIVER={MySQL ODBC 8.0 ANSI Driver};SERVER=localhost;PORT=3306;DATABASE=testdb;UID=root;PWD=root;",
        SQL_NTS,
        retconstring,
        1024,
        NULL,
        SQL_DRIVER_COMPLETE)) {


    case SQL_SUCCESS:
    case SQL_SUCCESS_WITH_INFO:
        cout << "Successfully connected to SQL Server\n";
        break;

    case SQL_INVALID_HANDLE:
    case SQL_ERROR:
        cout << "Could not connect to SQL Server\n";
        goto COMPLETED;

    default:
        break;
    }

    // ���� ���������� �� �����������, �� ������� �� ���������
    if (SQL_SUCCESS != SQLAllocHandle(SQL_HANDLE_STMT, sqlConnHandle, &sqlStmtHandle))
        goto COMPLETED;

    cout << "\nExecuting T-SQL query...\n";

    // ���� ���������� ������� � ��������, �� ������� �� ���������
    if (SQL_SUCCESS != SQLExecDirect(sqlStmtHandle, (SQLWCHAR*)L"SELECT * from test", SQL_NTS)) {
        cout << "Error querying SQL Server \n";
        goto COMPLETED;
    }
    else {

        //���������� ��������� ������ ��� ���������� ������� ������ SQL
        SQLCHAR sqlVersion[SQL_RESULT_LEN];
        SQLLEN sql_str_length;
        // ���������� ��� �������� ����� ��������
        SQLSMALLINT    V_OD_colanz, V_OD_rowcount;
        SQLINTEGER   V_OD_err, V_OD_id;
        SQLCHAR     V_OD_buffer[200];

        V_OD_err = SQLBindCol(sqlStmtHandle, 1, SQL_INTEGER, &V_OD_id, sizeof(V_OD_id), nullptr);
        V_OD_err = SQLBindCol(sqlStmtHandle, 2, SQL_CHAR, &V_OD_buffer, SQL_RESULT_LEN, &sql_str_length);

        // ������� �������� ����� ��������
        V_OD_err = SQLNumResultCols(sqlStmtHandle, &V_OD_colanz);
        cout << "Col count: " << V_OD_colanz << endl;

        V_OD_err = SQLRowCount(sqlStmtHandle, &sql_str_length);
        cout << "Row count: " << sql_str_length << endl;

        while (SQLFetch(sqlStmtHandle) != SQL_NO_DATA) {
            //������� �� ����� ������ SQL          
            cout << "Id: " << V_OD_id << ", name: " << V_OD_buffer << endl;
        }
    }

    // ��������� ���������� � ������� �� ���������
COMPLETED:
    SQLFreeHandle(SQL_HANDLE_STMT, sqlStmtHandle);
    SQLDisconnect(sqlConnHandle);
    SQLFreeHandle(SQL_HANDLE_DBC, sqlConnHandle);
    SQLFreeHandle(SQL_HANDLE_ENV, sqlEnvHandle);

    // ����� ����� ��������� ����������� ����������
    cout << "\nPress any key to exit...";
    getchar();
}


/*
����� ���������� MySQL � ODBC Windows

SQLAllocHandle	�������� ���������� ���������� � ����� ������.
SQLSetEnvAttr	������ ��������, ������� ��������� ����������� � ����� ������.
SQLConnect	������������� ����������� � �������� ���� ������.
SQLDriverConnect	�������� ������������� SQLConnect, � ���� ������� ������ ����������, ��������, ��� ������������ ���������� ���� ��� ������ ��������� ������.
SQLExecDirect	��� ����� ������� ������ ��������� ���������� SQL ��� ������������ ����������.
SQLFetch	��������� ��������� ����� ����� ������ �� ��������������� ������ � ���������� ������ ��� ���� ��������� ��������.
SQLGetData	��������� ������ ��� ������ ������� � �������������� ������.
SQLDisconnect	��������� �����������, ��������� � ���������� ������������.
SQLFreeHandle	����������� ���������� ���������� � ����� ������.

SQLBindCol	��������� ����� � ��� ������ �� ��������� ������.
SQLGetData	���������� ������ ������ ������� � ������� ������.
SQLNumResultCols	���������� ����� �������� � ������ ������� ������ ����� ���������� ��� ���������� SQL-��������� ���� SELECT.
SQLRowCount	���������� ����� �����, ���������� � ���������� �������.
*/