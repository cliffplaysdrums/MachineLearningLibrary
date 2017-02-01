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

// Prototypes
template <typename T> T operator*(const T&, const Row<T>&);

 
template <typename T> class Row {
	public:
		vector<T> contents;
		string lastError; // error message to aid debugging
		
		Row(); // constructor
		
		// public functions
		void push_back(T item) { contents.push_back(item); }
		void pop_back() { contents.pop_back(); }
		size_t size() { return contents.size(); }
		bool empty() { return contents.size(); }
		
		// operator overloading
		T operator*(const Row<T>&);
		T operator*(const T&);
		T operator[](const size_t& index) { return contents[index]; };
};


/* Constructor */
template <typename T> 
Row<T>::Row() {
	lastError = "";
}


/* Overload Row<T> * Row<T> to return a sum of products of the corresponding 
 element of 2 rows */
template <typename T>
T Row<T>::operator*(const Row<T>& other) {
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


/* Overload Row<T> * T to return a sum of products */
template <typename T>
T Row<T>::operator*(const T& other) {
	T sumOfProducts = 0;
	
	for (T elem : contents) {
		sumOfProducts += elem * other;
	}
	
	return sumOfProducts;
}


/* Overload T * Row<T> to return a sum of products */
template <typename T>
T operator*(const T& primitive, const Row<T>& other) {
	T sumOfProducts = 0;
	
	for (T elem : other.contents) {
		sumOfProducts += elem * primitive;
	}
	
	return sumOfProducts;
}

