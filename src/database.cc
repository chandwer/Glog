#include "database.h"
#include <iostream>
using namespace std;

Database::Database(char *filename)
{
	database=NULL;
	isNew=stat(filename, &file)?true:false;
	open(filename);
}
Database::~Database() {}

bool Database::open(char *filename)
	{ return (sqlite3_open(filename, &database)==SQLITE_OK)?true:false; }

vector<vector<string> > Database::query(char *query)
{
	sqlite3_stmt *statement;
	vector<vector<string> > results;

	if(sqlite3_prepare_v2(database, query, -1, &statement, 0) == SQLITE_OK)
	{
		int cols=sqlite3_column_count(statement);
		int result=0;

		while(1)
		{
			result=sqlite3_step(statement);
			if(result==SQLITE_ROW)
			{
				vector<string> values;
				for(int col=0; col<cols; col++)
					values.push_back( (char*)sqlite3_column_text(statement, col));
				results.push_back(values);
			}
			else
				break;

		}
		sqlite3_finalize(statement);
	}
	else
	{
		string error=sqlite3_errmsg(database);
		if(error != "not an error")
			cout << query << " " << error << endl;
	}
	return results;
}

void Database::close()
{
	sqlite3_close(database);
}
