/*
glog

Chris Handwerker (2013) <chris.handwerker@gmail.com>
http://homebrewtechnology.org

Provides signal handlers for glog GTK interface
*/

#include "glog.h"

GlogWindow::GlogWindow(BaseObjectType *object, const Glib::RefPtr<Gtk::Builder> &glade)
:Gtk::Window(object), m_refGlade(glade), 
dateButton(0), utcButton(0), enterButton(0), clearButton(0), updateButton(0), dateEntry(0), utcEntry(0), callEntry(0), freqEntry(0), modeEntry(0), txrstEntry(0), rxrstEntry(0), remarksTextView(0), tagsTextView(0), logTreeView(0)
{
	// Load database
	Glib::ustring path="../glog.db";
	db=new Database(&path);

	// Get widgets
	glade->get_widget("dateButton", dateButton);
	glade->get_widget("utcButton", utcButton);
	glade->get_widget("enterButton", enterButton);
	glade->get_widget("clearButton", clearButton);
	glade->get_widget("updateButton", updateButton);

	glade->get_widget("dateEntry", dateEntry);
	glade->get_widget("utcEntry", utcEntry);
	glade->get_widget("callEntry", callEntry);
	glade->get_widget("freqEntry", freqEntry);
	glade->get_widget("modeEntry", modeEntry);
	glade->get_widget("txrstEntry", txrstEntry);
	glade->get_widget("rxrstEntry", rxrstEntry);

	glade->get_widget("remarksTextView", remarksTextView);
	glade->get_widget("tagsTextView", tagsTextView);

	glade->get_widget("logTreeView", logTreeView);

	// Get buffers
	remarksBuffer=remarksTextView->get_buffer();
	tagsBuffer=tagsTextView->get_buffer();

	// Create tree model
	logListStore=Gtk::ListStore::create(m_columns);
	logTreeView->set_model(logListStore);

	// Connect signals
	dateButton->signal_clicked().connect(sigc::mem_fun(this, &GlogWindow::dateButton_clicked));
	utcButton->signal_clicked().connect(sigc::mem_fun(this, &GlogWindow::utcButton_clicked));
	enterButton->signal_clicked().connect(sigc::mem_fun(this, &GlogWindow::enterButton_clicked));
	clearButton->signal_clicked().connect(sigc::mem_fun(this, &GlogWindow::clearButton_clicked));
	updateButton->signal_clicked().connect(sigc::mem_fun(this, &GlogWindow::updateButton_clicked));

	// Add TreeView's view columns
	logTreeView->append_column("Date", m_columns.m_col_date);
	logTreeView->append_column("Time", m_columns.m_col_time);
	logTreeView->append_column("Call", m_columns.m_col_call);
	logTreeView->append_column("Frequency", m_columns.m_col_frequency);
	logTreeView->append_column("Mode", m_columns.m_col_mode);
	logTreeView->append_column("RST TX", m_columns.m_col_rst_tx);
	logTreeView->append_column("RST RX", m_columns.m_col_rst_rx);
	updateButton_clicked();

}
GlogWindow::~GlogWindow() 
{
}

void GlogWindow::tag_parse()
{
	// TODO replace tag parser with something more flexible
	tags.clear();
	istringstream ss(tagsBuffer->get_text());
	string token;

	while(std::getline(ss, token, ' '))
		tags.push_back(token);
}
void GlogWindow::updateButton_clicked()
{
	tag_parse();
	vector<vector<Glib::ustring> > log=db->get_contacts(tags);

	logListStore->clear();
	Gtk::TreeModel::Row treerow;

	for(vector<Glib::ustring> row : log)
	{
		treerow=*(logListStore->append());

		treerow[m_columns.m_col_date]=row[1].data();
		treerow[m_columns.m_col_time]=row[2].data();
		treerow[m_columns.m_col_call]=row[3].data();
		treerow[m_columns.m_col_frequency]=row[4].data();
		treerow[m_columns.m_col_mode]=row[5].data();
		treerow[m_columns.m_col_rst_tx]=row[6].data();
		treerow[m_columns.m_col_rst_rx]=row[7].data();

		/*
		for(Glib::ustring col : row)
		{
			cout << col.data() << "\t";
		}
		cout << endl;
		*/
	}
}
void GlogWindow::dateButton_clicked()
{
	// set dateEntry with current date in yyyy-mm-dd format
	time_t now=time(0);
	tm *ltm=gmtime(&now);

	stringstream ss;
	ss << 1900+ltm->tm_year << "-" << ltm->tm_mon << "-" << ltm->tm_mday;
	dateEntry->set_text(ss.str());
}
void GlogWindow::utcButton_clicked()
{
	// set utcEntry with current time in hh:mm format
	time_t now=time(0);
	tm *ltm=gmtime(&now);

	stringstream ss;
	ss << ltm->tm_hour << ":" << ltm->tm_min;
	utcEntry->set_text(ss.str());
}
void GlogWindow::enterButton_clicked()
{
	tag_parse();

	db->set_contact(
			callEntry->get_text(),
			modeEntry->get_text(),
			dateEntry->get_text(),
			utcEntry->get_text(),
			freqEntry->get_text(),
			rxrstEntry->get_text(),
			txrstEntry->get_text(),
			remarksBuffer->get_text(),
			tags
		);
	callEntry->set_text("");
	txrstEntry->set_text("");
	rxrstEntry->set_text("");
	remarksBuffer->set_text("");
	updateButton_clicked();
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
	remarksBuffer->set_text("");
	tagsBuffer->set_text("");
}
