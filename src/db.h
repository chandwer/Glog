/*
db

Chris Handwerker (2013) <chris.handwerker@gmail.com>
http://homebrewtechnology.org

Methods for creating and interacting with the Sqlite3 database
*/

#ifndef DB_H
#define DB_H

#include <sqlite3.h>
#include <gtkmm.h> 

class Database
{
	public:
		Database(Glib::ustring *filename);
		~Database();

	private:
		// TODO making a vector of type Glib::ustring doesn't work I guess... fix this
		vector<vector<Glib::ustring> > Query(Glib::ustring *query);

		sqlite3 *db;
};

#endif
