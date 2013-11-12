#ifndef GLOGWINDOW_H
#define GLOGWINDOW_H
#include <gtkmm.h>

class GlogWindow : public Gtk::Window
{
	public:
		GlogWindow(BaseObjectType *object, const Glib::RefPtr<Gtk::Builder> &glade);
		virtual ~GlogWindow();
	protected:
		// Signal handlers
		void enterButton_clicked();
		void clearButton_clicked();

		// Member widgets
		Glib::RefPtr<Gtk::Builder> m_refGlade;

		Gtk::Button *enterButton;
		Gtk::Button *clearButton;

		Gtk::Entry *callEntry;
};
#endif
