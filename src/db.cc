/*
db

Chris Handwerker (2013) <chris.handwerker@gmail.com>
http://homebrewtechnology.org

Methods for creating and interacting with the Sqlite3 database
*/

#include "db.h"

Database::Database(Glib::ustring *filename)
{
	// Create database
	sqlite3_open(filename->c_str(), &db);
	
}
Database::~Database() 
{
	sqlite3_close(db);
}

vector<vector<Glib::ustring> > Database::Query(Glib::ustring *query)
{
	sqlite3_stmt *statement;
	vector<vector<Glib::ustring> > results;

	if(sqlite3_prepare_v2(db, (const char *)query->c_str(), -1, &statement, 0)==SQLITE_OK)
	{
		int cols=sqlite3_column_count(statement);
		while(sqlite3_step(statement)==SQLITE_ROW)
		{
			// build a vector row and push it to results vector
			vector<Glib::ustring> values;
			for(int i=0; i<cols; i++)
				values.push_back( (Glib::ustring *)sqlite3_column_text(statement, i));
			results.push_back(values);
		}
		sqlite3_finalize(statement);
	}
}
