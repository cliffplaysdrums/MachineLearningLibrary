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
 
 #include <vector>
 #include <memory>
 #include <iostream>
 
 typedef long double lDouble;
 
 /* Container for all data gained from file */
 typedef struct {
 	size_t sampleCount;
 	size_t featureCount;
 	std::vector<std::unique_ptr<lDouble[]> > data;
 	std::vector<lDouble> target;
 } fileContents_t;
 
 
 class Parser {
 	std::unique_ptr<fileContents_t> fileContents;
 	public:
 		Parser(size_t);
 		std::unique_ptr<fileContents_t> getData();
 };
 
 // Constructor
 Parser::Parser(size_t numFeatures) {
 	fileContents = std::make_unique<fileContents_t>();
 	fileContents->featureCount = numFeatures;
 }
 
 std::unique_ptr<fileContents_t> Parser::getData() {
 	fileContents->data.push_back(
 		std::unique_ptr<lDouble[]>(new lDouble[fileContents->featureCount]));
 	fileContents->data[0][0] = 1;
 	fileContents->data[0][1] = 2;
 	fileContents->data[0][2] = 3;
 	
 	return std::move(fileContents);
 }
 
 int main() {
 	Parser P(5);
 	std::unique_ptr<fileContents_t> fileContents = P.getData();
 	// How do I extract parts of the struct?
 	// E.g. std::vector<std::unique_ptr<lDouble[]> > data = fileContents->data;
 	std::cout << fileContents->data[0][0] << std::endl;
 	return 0;
 }
