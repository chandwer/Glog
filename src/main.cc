#include <gtkmm/application.h>
#include "glog.h"

int main(int argc, char *argv[])
{
	Glib::RefPtr<Gtk::Application> app=Gtk::Application::create(argc, argv);
	Glib::RefPtr<Gtk::Builder> builder=Gtk::Builder::create();

	builder->add_from_file("glog.glade");
	GlogWindow *glog;

	builder->get_widget_derived("GlogWindow", glog);

	return app->run(*glog);
}
