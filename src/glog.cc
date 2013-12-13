/*
glog

Chris Handwerker (2013) <chris.handwerker@gmail.com>
http://homebrewtechnology.org

Provides signal handlers for glog GTK interface
*/

#include "glog.h"
#include <iostream>
#include <string>
#include <vector>

using namespace std;

GlogWindow::GlogWindow(BaseObjectType *object, const Glib::RefPtr<Gtk::Builder> &glade)
:Gtk::Window(object), m_refGlade(glade), 
enterButton(0), clearButton(0), dateEntry(0), utcEntry(0), callEntry(0), freqEntry(0), modeEntry(0), txrstEntry(0), rxrstEntry(0)
{
	// Load database
	Glib::ustring path="../glog.db";
	db=new Database(&path);
	// if(db->isNew)
	// 	this->newDatabase();

	// Get widgets
	glade->get_widget("enterButton", enterButton);
	glade->get_widget("clearButton", clearButton);

	glade->get_widget("dateEntry", dateEntry);
	glade->get_widget("utcEntry", utcEntry);
	glade->get_widget("callEntry", callEntry);
	glade->get_widget("freqEntry", freqEntry);
	glade->get_widget("modeEntry", modeEntry);
	glade->get_widget("txrstEntry", txrstEntry);
	glade->get_widget("rxrstEntry", rxrstEntry);

	// Connect signals
	//enterButton->signal_clicked().connect(sigc::mem_fun(this, &GlogWindow::enterButton_clicked));
	//clearButton->signal_clicked().connect(sigc::mem_fun(this, &GlogWindow::clearButton_clicked));

}
GlogWindow::~GlogWindow() 
{
}

/*
void GlogWindow::enterButton_clicked()
{
	Glib::ustring query;

	query="INSERT INTO contacts (call, mode, frequency, date, utc, rst_tx, rst_rx) VALUES (";
	query+="'"+callEntry->get_text()+"',";
	query+="'"+modeEntry->get_text()+"',";
	query+="'"+freqEntry->get_text()+"',";
	query+="'"+dateEntry->get_text()+"',";
	query+="'"+utcEntry->get_text()+"',";
	query+="'"+txrstEntry->get_text()+"',";
	query+="'"+rxrstEntry->get_text()+"'";
	query+=");";

	db->query(query.c_str());
	this->clearButton_clicked();
}
void GlogWindow::clearButton_clicked()
{
	dateEntry->set_text("");
	utcEntry->set_text("");
	callEntry->set_text("");
	freqEntry->set_text("");
	modeEntry->set_text("");
	txrstEntry->set_text("");
	rxrstEntry->set_text("");
}
void GlogWindow::newDatabase()
{
	db->query("CREATE TABLE contacts("
				"contact_id INTEGER PRIMARY KEY AUTOINCREMENT,"
				"call TEXT,"
				"mode TEXT,"
				"frequency TEXT,"
				"date TEXT,"
				"utc TEXT,"
				"rst_tx INTEGER,"
				"rst_rx INTEGER"
			");");
}
*/
