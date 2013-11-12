#ifndef GLOGWINDOW_H
#define GLOGWINDOW_H
#include <gtkmm.h>
#include "database.h"

class GlogWindow : public Gtk::Window
{
	public:
		GlogWindow(BaseObjectType *object, const Glib::RefPtr<Gtk::Builder> &glade);
		virtual ~GlogWindow();
	protected:
		Database *db;
		void newDatabase();

		// Signal handlers
		void enterButton_clicked();
		void clearButton_clicked();

		// Member widgets
		Glib::RefPtr<Gtk::Builder> m_refGlade;

		Gtk::Button *enterButton;
		Gtk::Button *clearButton;

		Gtk::Entry *dateEntry;
		Gtk::Entry *utcEntry;
		Gtk::Entry *callEntry;
		Gtk::Entry *freqEntry;
		Gtk::Entry *modeEntry;
		Gtk::Entry *txrstEntry;
		Gtk::Entry *rxrstEntry;
};
#endif
