CC		= g++
CFLAG 	= `pkg-config gtkmm-3.0 --cflags --libs`

glog: main.cc glog.cc
	$(CC) main.cc glog.cc -o glog $(CFLAG)
	
