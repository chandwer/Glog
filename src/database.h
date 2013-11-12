#ifndef DATABASE_H
#define DATABASE_H

#include <sqlite3.h>
#include <sys/stat.h>
#include <string>
#include <vector>

using namespace std;

class Database
{
	public:
		Database(char *filename);
		~Database();

		bool open(char *filename);
		vector<vector<string> > query(const char *query);
		void close();

		bool isNew;

	private:
		sqlite3 *database;
		struct stat file;

};
#endif
