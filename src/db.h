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
		void set_contact(Glib::ustring call, Glib::ustring mode, Glib::ustring date, Glib::ustring utc, Glib::ustring freq, Glib::ustring rxrst, Glib::ustring txrst, Glib::ustring remarks, Glib::ustring tags);	

		vector<vector<Glib::ustring> > results;

	private:
		void query();
		void init_db();

		Glib::ustring get_id(Glib::ustring *value, Glib::ustring type, Glib::ustring table);

		// internal variables
		sqlite3 *db;
		Glib::ustring statement;
		Glib::ustring call_copy;
};

#endif
