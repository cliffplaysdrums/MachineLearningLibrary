CC = g++
CFLAGS = -Wall -std=c++17
LIBS = -lpthread
SOURCES = csvParser.cpp Row.cpp MachMatrix.cpp
HEADERS = headers.h headers/types.h

all: $(SOURCES) $(HEADERS)
	$(CC) csvParser.cpp -o csvParser $(CFLAGS) $(LIBS)

clean: 
	rm csvParser
