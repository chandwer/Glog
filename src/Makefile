CC		= g++
CFLAG 	= `pkg-config gtkmm-3.0 --cflags --libs` -lsqlite3

glog: main.cc glog.cc database.cc
	$(CC) main.cc glog.cc database.cc -o glog $(CFLAG)
	
