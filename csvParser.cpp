/* csvParser.cpp
 * 
 * Author: Cliff Chandler <cliffplaysdrums@gmail.com>
 *
 * License: GPL
 *
 * This class provides tools to parse a CSV file for machine learning.
 * The '#' character at the beginning of a line in the CSV file is treated as a
 * comment.
 * The user must know the number of features.
 */
 
 #include "headers.h" 
 #include <iostream>
 
 /* Container for all data gained from file */
 typedef struct {
 	size_t sampleCount;
 	size_t featureCount;
 	MachMatrix data;
 	MachVector target;
 } fileContents_t;
 
 
 class Parser {
 	fileContents_t fileContents;
 	public:
 		Parser();
 		fileContents_t *getData();
 };
 
 // Constructor
 Parser::Parser() {

 }
 
 fileContents_t *Parser::getData() {
 	
 	return &fileContents;
 }
 
 int main() {
 	Parser P();
 	return 0;
 }
