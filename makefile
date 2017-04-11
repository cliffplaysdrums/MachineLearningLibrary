CC = g++
CFLAGS = -Wall -std=c++17
LIBS = -lpthread
DEBUG = -g
SOURCES = csvParser.cpp Row.cpp MachMatrix.cpp
HEADERS = headers.h headers/types.h

all: $(SOURCES) $(HEADERS)
	$(CC) csvParser.cpp -o csvParser $(CFLAGS) $(LIBS)
	
debug: $(SOURCES) $(HEADERS)
	$(CC) $(DEBUG) csvParser.cpp -o csvParser $(CFLAGS) $(LIBS)

clean: 
	rm csvParser
