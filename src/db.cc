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
	results=new vector<vector<Glib::ustring> >;

	statement=new Glib::ustring("SELECT * FROM sqlite_master WHERE type='table';");
	query();

	if(results->size()!=5)
		init_db();
}
Database::~Database() 
{
	sqlite3_close(db);
}

void Database::query()
{
	sqlite3_stmt *stmt;
	results->clear();

	if(sqlite3_prepare_v2(db, (const char *)statement->c_str(), -1, &stmt, 0)==SQLITE_OK)
	{
		int cols=sqlite3_column_count(stmt);

		while(sqlite3_step(stmt)==SQLITE_ROW)
		{
			// build a vector row and push it to results vector
			vector<Glib::ustring> *values=new vector<Glib::ustring>;
			for(int i=0; i<cols; i++)
			{
				Glib::ustring *column=new Glib::ustring((const char*)sqlite3_column_text(stmt, i));
				values->push_back(*column);
			}
			results->push_back(*values);
		}
		sqlite3_finalize(stmt);
	}
	else
		cerr << "Error in query: " << *statement << " " << sqlite3_errmsg(db) << endl;
}
void Database::init_db()
{
	// build new database, returns true on success
	statement=new Glib::ustring(
	"CREATE TABLE contacts(\""
		"contact_id INTEGER PRIMARY KEY AUTOINCREMENT,"
		"call_id INTEGER,"
		"mode_id INTEGER,"
		"date TEXT,"
		"utc TEXT,"
		"frequency REAL,"
		"rst_tx INTEGER,"
		"rst_rx INTEGER,"
		"remarks TEXT"
	"\");");
	query();

	statement=new Glib::ustring(
	"CREATE TABLE stations(\""
		"call_id INTEGER PRIMARY KEY AUTOINCREMENT,"
		"call TEXT"
	"\");");
	query();

	statement=new Glib::ustring(
	"CREATE TABLE modes(\""
			"mode_id INTEGER PRIMARY KEY AUTOINCREMENT,"
			"mode TEXT"
		"\");");
	query();
	
	statement=new Glib::ustring(
	"CREATE TABLE tags(\""
			"tag_id INTEGER PRIMARY KEY AUTOINCREMENT,"
			"tag TEXT"
		"\");");
	query();

	statement=new Glib::ustring(	
	"CREATE TABLE tag_contact(\""
			"contact_id INTEGER PRIMARY KEY AUTOINCREMENT,"
			"tag_id INTEGER"
		"\");");
	query();
}
