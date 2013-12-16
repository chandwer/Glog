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

using namespace std;

class GlogWindow : public Gtk::Window
{
	public:
		GlogWindow(BaseObjectType *object, const Glib::RefPtr<Gtk::Builder> &glade);
		virtual ~GlogWindow();
	protected:
		Database *db;

		// TODO move tag parsing to a friend class
		vector<Glib::ustring> tags;
		void tag_parse();

		// Text buffers
		Glib::RefPtr<Gtk::TextBuffer> remarksBuffer, tagsBuffer;

		// Signal handlers
		void dateButton_clicked();
		void utcButton_clicked();
		void enterButton_clicked();
		void clearButton_clicked();
		void updateButton_clicked();

		// Member widgets
		Glib::RefPtr<Gtk::Builder> m_refGlade;

		Gtk::Button *dateButton;
		Gtk::Button *utcButton;
		Gtk::Button *enterButton;
		Gtk::Button *clearButton;
		Gtk::Button *updateButton;

		Gtk::Entry *dateEntry;
		Gtk::Entry *utcEntry;
		Gtk::Entry *callEntry;
		Gtk::Entry *freqEntry;
		Gtk::Entry *modeEntry;
		Gtk::Entry *txrstEntry;
		Gtk::Entry *rxrstEntry;

		Gtk::TextView *remarksTextView;
		Gtk::TextView *tagsTextView;

		// Tree model
		class ModelColumns : public Gtk::TreeModel::ColumnRecord
		{
			public:
				ModelColumns()
				{ add(m_col_date); add(m_col_time); add(m_col_call); add(m_col_frequency); }

				Gtk::TreeModelColumn<Glib::ustring> m_col_date;
				Gtk::TreeModelColumn<Glib::ustring> m_col_time;
				Gtk::TreeModelColumn<Glib::ustring> m_col_call;
				Gtk::TreeModelColumn<Glib::ustring> m_col_frequency;
		};
		ModelColumns m_columns;

		Gtk::TreeView *logTreeView;
		Glib::RefPtr<Gtk::ListStore> logListStore;
};
#endif
