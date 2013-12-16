/*
main

Chris Handwerker (2013) <chris.handwerker@gmail.com>
http://homebrewtechnology.org

Builds GTK window from glog.glade definition file and launches application.
*/

#include <gtkmm/application.h>
#include "glog.h"

int main(int argc, char *argv[])
{
	Glib::RefPtr<Gtk::Application> app=Gtk::Application::create(argc, argv);
	Glib::RefPtr<Gtk::Builder> builder=Gtk::Builder::create();

	// Build GTK window from glade file
	builder->add_from_file("glog.glade");

	// Bind window to GlogWindow object 
	GlogWindow *glog;
	builder->get_widget_derived("GlogWindow", glog);

	return app->run(*glog);
}
