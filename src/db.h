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
#include <vector>
#include <iostream>

using namespace std;

class Database
{
	public:
		Database(Glib::ustring *filename);
		~Database();

		vector<vector<Glib::ustring> > *results;

	private:
		void query();
		void init_db();

		// internal variables
		sqlite3 *db;
		Glib::ustring *statement;
};

#endif
