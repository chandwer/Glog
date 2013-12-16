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

	statement="SELECT * FROM sqlite_master WHERE type='table';";
	query();

	if(results.size()!=6)
		init_db();
}
Database::~Database() 
{
	sqlite3_close(db);
}
void Database::set_contact(Glib::ustring call, Glib::ustring mode, Glib::ustring date, Glib::ustring utc, Glib::ustring freq, Glib::ustring rxrst, Glib::ustring txrst, Glib::ustring remarks, Glib::ustring tags)
{
	// Get station and mode ids
	Glib::ustring call_id=get_id(&call,"call","stations");
	Glib::ustring mode_id=get_id(&mode,"mode","modes");

	// Create contact entry
	statement="INSERT INTO contacts(call_id, mode_id, date, utc, frequency, rst_tx, rst_rx,remarks) VALUES ("
					"'"+call_id+"', ";
					"'"+mode_id+"', ";
					"'"+date+"', ";
					"'"+utc+"', ";
					"'"+freq+"', ";
					"'"+rsttx+"', ";
					"'"+rstrx+"', ";
					"'"+remarks+"'";
				");";
	// Associate tags in tag_contact

	cout << station_id << "\t" << mode_id << endl;
}
Glib::ustring Database::get_id(Glib::ustring *value, Glib::ustring type, Glib::ustring table)
{
	Glib::ustring select="SELECT "+type+"_id FROM "+table+" WHERE "+type+"='"+*value+"';";
	Glib::ustring insert="INSERT INTO "+table+"("+type+") VALUES ('"+*value+"');";

	statement=select; query();
	if(results.size()==0)
	{
		statement=insert; query();
		statement=select; query();
	}
	return results[0][0];
}
void Database::query()
{
	sqlite3_stmt *stmt;
	results.clear();

	if(sqlite3_prepare_v2(db, (const char *)statement.c_str(), -1, &stmt, 0)==SQLITE_OK)
	{
		int cols=sqlite3_column_count(stmt);

		while(sqlite3_step(stmt)==SQLITE_ROW)
		{
			// build a vector row and push it to results vector
			vector<Glib::ustring> values;
			for(int i=0; i<cols; i++)
			{
				Glib::ustring column=(const char*)sqlite3_column_text(stmt, i);
				values.push_back(column);
			}
			results.push_back(values);
		}
		sqlite3_finalize(stmt);
	}
	else
		cerr << "Error in query: " << statement << " " << sqlite3_errmsg(db) << endl;
}
void Database::init_db()
{
	// build new database, returns true on success
	statement=
	"CREATE TABLE contacts("
		"contact_id INTEGER PRIMARY KEY AUTOINCREMENT,"
		"call_id INTEGER,"
		"mode_id INTEGER,"
		"date TEXT,"
		"utc TEXT,"
		"frequency REAL,"
		"rst_tx INTEGER,"
		"rst_rx INTEGER,"
		"remarks TEXT"
	");";
	query();

	statement=
	"CREATE TABLE stations("
		"call_id INTEGER PRIMARY KEY AUTOINCREMENT,"
		"call TEXT"
	");";
	query();

	statement=
	"CREATE TABLE modes("
			"mode_id INTEGER PRIMARY KEY AUTOINCREMENT,"
			"mode TEXT"
		");";
	query();
	
	statement=
	"CREATE TABLE tags("
			"tag_id INTEGER PRIMARY KEY AUTOINCREMENT,"
			"tag TEXT"
		");";
	query();

	statement=
	"CREATE TABLE tag_contact("
			"contact_id INTEGER PRIMARY KEY AUTOINCREMENT,"
			"tag_id INTEGER"
		");";
	query();
}
