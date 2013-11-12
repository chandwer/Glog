#include "glog.h"
#include <iostream>

GlogWindow::GlogWindow(BaseObjectType *object, const Glib::RefPtr<Gtk::Builder> &glade)
:Gtk::Window(object), m_refGlade(glade), 
enterButton(0), clearButton(0), dateEntry(0), utcEntry(0), callEntry(0), freqEntry(0), modeEntry(0), txrstEntry(0), rxrstEntry(0)
{
	// Load database
	db=new Database("../glog.db");
	if(db->isNew)
		this->newDatabase();

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
	enterButton->signal_clicked().connect(sigc::mem_fun(this, &GlogWindow::enterButton_clicked));
	clearButton->signal_clicked().connect(sigc::mem_fun(this, &GlogWindow::clearButton_clicked));

}
GlogWindow::~GlogWindow() 
{
}

void GlogWindow::enterButton_clicked()
{
	std::cout << "Call: " << callEntry->get_text() << std::endl;	
}
void GlogWindow::clearButton_clicked()
{
	std::cout << "Clear fields" << std::endl;
}
void GlogWindow::newDatabase()
{
	db->query("CREATE TABLE stations(call_id INTEGER PRIMARY KEY AUTOINCREMENT, call TEXT);");
	db->query("CREATE TABLE modes(mode_id INTEGER PRIMARY KEY AUTOINCREMENT, mode TEXT);");
	db->query("CREATE TABLE contacts("
				"contact_id INTEGER PRIMARY KEY AUTOINCREMENT,"
				"call_id INTEGER,"
				"mode_id INTEGER,"
				"frequency REAL,"
				"date TEXT,"
				"utc TEXT,"
				"rst_tx INTEGER,"
				"rst_rx INTEGER"
			");");
}
