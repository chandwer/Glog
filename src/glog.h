/*
glog

Chris Handwerker (2013) <chris.handwerker@gmail.com>
http://homebrewtechnology.org

Provides signal handlers for glog GTK interface
*/

#ifndef GLOGWINDOW_H
#define GLOGWINDOW_H
#include <gtkmm.h>
#include <iostream>
#include <vector>
#include <ctime>
#include "db.h"

class GlogWindow : public Gtk::Window
{
	public:
		GlogWindow(BaseObjectType *object, const Glib::RefPtr<Gtk::Builder> &glade);
		virtual ~GlogWindow();
	protected:
		Database *db;
		void newDatabase();

		// Signal handlers
		void dateButton_clicked();
		void utcButton_clicked();
		void enterButton_clicked();
		void clearButton_clicked();

		// Member widgets
		Glib::RefPtr<Gtk::Builder> m_refGlade;

		Gtk::Button *dateButton;
		Gtk::Button *utcButton;
		Gtk::Button *enterButton;
		Gtk::Button *clearButton;

		Gtk::Entry *dateEntry;
		Gtk::Entry *utcEntry;
		Gtk::Entry *callEntry;
		Gtk::Entry *freqEntry;
		Gtk::Entry *modeEntry;
		Gtk::Entry *txrstEntry;
		Gtk::Entry *rxrstEntry;

		Gtk::TextView *remarksTextView;
		Gtk::TextView *tagsTextView;
};
#endif
