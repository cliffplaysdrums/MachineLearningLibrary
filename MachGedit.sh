#!/bin/bash

# Opens Mach source files currently in development

SOURCES='csvParser.cpp headers.h Row.cpp headers/types.h MachMatrix.cpp'
nohup gedit $SOURCES > /dev/null 2>&1&
