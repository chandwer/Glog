CC		= g++
CFLAG 	= `pkg-config gtkmm-3.0 --cflags --libs` -lsqlite3

all: glog

glog: main.o glog.o database.o
	$(CC) main.o glog.o db.o -o glog $(CFLAG)

main.o: main.cc
	$(CC) -c main.cc $(CFLAG)

glog.o: glog.cc
	$(CC) -c glog.cc $(CFLAG)

db.o: db.cc
	$(CC) -c db.cc
