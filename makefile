CC = g++
CFLAGS = -Wall -std=c++17
SOURCES = csvParser.cpp Row.cpp MachMatrix.cpp
HEADERS = headers.h headers/types.h

all: $(SOURCES) $(HEADERS)
	$(CC) csvParser.cpp -o csvParser $(CFLAGS)

clean: 
	rm csvParser
