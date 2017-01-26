/* Row.cpp
 * 
 * Author: Cliff Chandler <cliffplaysdrums@gmail.com>
 *
 * License: GPL
 *
 * This class is a data structure for holding rows of a matrix and providing
 * added functionality such as multiplication of whole rows
 */
 
 /* TODO:
  *	Consider making 'contents' private and overload operators to access it
  *	Make push_back and pop_back check for error and return int
  */
 
#include "headers.h"
#include <string>

using std::string;
using std::vector;
 
 
template <typename T> class Row {
	public:
		vector<T> contents;
		string lastError; // error message to aid debugging
		
		Row(); // constructor
		
		// public functions
		void push_back(T item) { contents.push_back(item); }
		void pop_back() { contents.pop_back(); }
		
		// operator overloading
		MachDouble operator*(const Row<T>&);
};


template <typename T> 
Row<T>::Row() {
	lastError = "";
}


/* Define * operator to return a sum of products of the corresponding elements
 of 2 rows of equal size */
template <typename T>
MachDouble Row<T>::operator*(const Row<T>& other) {
	if (contents.size() != other.contents.size()) {
		lastError = "Multiplied to multiply 2 rows of different lengths";
	}
	
	T sumOfProducts = 0;
	size_t index = 0;
	
	for(T elem : contents) {
		sumOfProducts += elem * other.contents[index];
		index++;
	}
	
	return sumOfProducts;
}

