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
 
 using Mach::Row;
 using Mach::MachMatrix;
  
 /* Container for all data gained from file */
 typedef struct {
 	size_t sampleCount;
 	size_t featureCount;
 	MachMatrix<MachDouble> data;
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
 void printMatrix(MachMatrix<MachDouble> mat) {
 	using namespace std;
 	for (size_t i=0; i<mat.size(); i++) {
 		for (size_t j=0; j<mat[0].size(); j++) {
 			cout << mat[i][j] << " ";
 		}
 		
 		cout << endl;
 	}
 }
 
 
 int main() {
 	using std::cout;
 	using std::endl;
 	
 	Parser P;
 	P.parse("Datasets/iris.csv");
 	fileContents_t fileContents = *(P.getData());
 	
 	cout << "Testing Mach Matrix" << endl;
 	
 	MachMatrix<MachDouble> A, B, C;
 	A.push_back(fileContents.data[0]);
 	A.push_back(fileContents.data[1]);
 	B.push_back(fileContents.data[2]);

 	B = B.transpose();
 	
 	cout << "A:" << endl;
 	printMatrix(A);
 	cout << "B:" << endl;
 	printMatrix(B);
 	
 	cout << "A*B" << endl;
 	printMatrix(A * B);
 	cout << endl << "Parallel:" << endl;
 	C = A.parallelMultiply(B);
 	printMatrix(C);
 	
 	return 0;
 }
