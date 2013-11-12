#include "glog.h"
#include <iostream>

GlogWindow::GlogWindow(BaseObjectType *object, const Glib::RefPtr<Gtk::Builder> &glade)
:Gtk::Window(object), m_refGlade(glade), enterButton(0), clearButton(0), callEntry(0)
{
	// Get widgets
	glade->get_widget("enterButton", enterButton);
	glade->get_widget("clearButton", clearButton);
	glade->get_widget("callEntry", callEntry);

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
