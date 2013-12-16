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
vector<vector<Glib::ustring> > Database::get_contacts(vector<Glib::ustring> tags)
{
	Glib::ustring where;

	for(int i=0; i<tags.size(); i++)
	{
		if(i==0)
			where+="WHERE ";
		where+="tags.tag='"+tags[i]+"'";

		if(i<tags.size()-1)
			where+=" AND ";
	}

	statement=
		"SELECT contacts.contact_id, contacts.date, contacts.utc, stations.call, contacts.frequency, modes.mode,"
				"contacts.rst_tx, contacts.rst_rx, contacts.remarks, tags.tag "
		"FROM contacts "
			"INNER JOIN stations ON contacts.call_id=stations.call_id "
			"INNER JOIN modes ON contacts.mode_id=modes.mode_id "
			"INNER JOIN tag_contact ON contacts.contact_id=tag_contact.contact_id "
			"INNER JOIN tags ON tag_contact.tag_id=tags.tag_id "
		+where+" GROUP BY contacts.contact_id;";

//cout << "STATEMENT IS ---> " << statement << endl << endl;

	query();
	return results;

}
void Database::set_contact(Glib::ustring call, Glib::ustring mode, Glib::ustring date, Glib::ustring utc, Glib::ustring freq, Glib::ustring rxrst, Glib::ustring txrst, Glib::ustring remarks, vector<Glib::ustring> tags)
{
	// Get station and mode ids
	Glib::ustring call_id=get_id(&call,"call","stations");
	Glib::ustring mode_id=get_id(&mode,"mode","modes");

	// Create contact entry
	statement="INSERT INTO contacts(call_id, mode_id, date, utc, frequency, rst_rx, rst_tx, remarks) VALUES ("
					"'"+call_id+"',"
					"'"+mode_id+"',"
					"'"+date+"',"
					"'"+utc+"',"
					"'"+freq+"',"
					"'"+rxrst+"',"
					"'"+txrst+"',"
					"'"+remarks+"'"
				");";
	query();
	statement="SELECT last_insert_rowid();"; query();
	Glib::ustring contact_id=results[0][0];

	// Associate tags in tag_contact
	for(Glib::ustring tag : tags)
	{
		Glib::ustring tag_id=get_id(&tag,"tag","tags");
		statement="INSERT INTO tag_contact(contact_id, tag_id) VALUES ('"+contact_id+"','"+tag_id+"');"; query();
	}
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
			"contact_id INTEGER,"
			"tag_id INTEGER"
		");";
	query();
}
