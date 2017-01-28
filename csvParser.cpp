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
 
 /* TODO: 
  *	Consider making this class generic to match Row.cpp
  */
 
 #include <iostream>
 #include <fstream>
 #include <sstream>
 #include "headers.h"
  
 /* Container for all data gained from file */
 typedef struct {
 	size_t sampleCount;
 	size_t featureCount;
 	MachMatrix data;
 	vector<MachDouble> target;
 } fileContents_t;
 
 
 class Parser {
 	fileContents_t fileContents;
 	public:
 		Parser();
 		int parse(const std::string&);
 		fileContents_t *getData();
 };
 
 // Constructor
 Parser::Parser() {

 }
 
 
 int Parser::parse(const std::string& FILENAME) {
 	std::ifstream file(FILENAME); // open file
 	if (file) {
	 	std::string line;
 		while(std::getline(file, line)) { // read line delimited by newline character
 			// check if line is empty or is a comment
 			if (line.size() == 0 || line.at(0) == '#') continue; // # is a comment
		 	std::stringstream ss(line);
		 	std::string item;
		 	Row<MachDouble> r;
	 	
		 	while(std::getline(ss, item, ',')) {
		 		r.push_back(std::stold(item));
		 	}
	 	
	 		r.pop_back(); // remove last item
	 		fileContents.target.push_back(std::stold(item));
		 	fileContents.data.push_back(r);
 		}
 	} else { // !file
 		std::cout << "File not found." << std::endl;
 	}
 	
 	return 0;
 }
 
 
 fileContents_t *Parser::getData() {
 	return &fileContents;
 }
 
 
 /*********************************************/
 int main() {
 	Parser P;
 	P.parse("Datasets/iris.csv");
 	long double test = 1.0;
 	fileContents_t fileContents = *(P.getData());
 	std::cout << test * fileContents.data[0] << std::endl;
 	return 0;
 }
