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


/* Overload MachDouble * Row<T> to return a sum of products */
template <typename T>
MachDouble operator*(const int primitive, const Mach::Row<T>& other) {
	MachDouble sumOfProducts = 0;
	
	for (MachDouble elem : other) {
		sumOfProducts += elem * primitive;
	}
	
	return sumOfProducts;
}


namespace Mach {
 
template <typename T> class Row {

	// typename is mandatory before a qualified dependent type
 	typedef typename vector<T>::iterator iterator;
	typedef typename vector<T>::const_iterator const_iterator;
	
	public:
		string lastError; // error message to aid debugging
		
		Row(); // constructor
		
		// public functions
		void push_back(T item) { contents.push_back(item); }
		void pop_back() { contents.pop_back(); }
		size_t size() const { return contents.size(); }
		bool empty() const { return contents.empty(); }
		
		// operator overloading
		T operator*(const Row<T>&);
		T operator*(const T&);
		T operator[](const size_t& index) { return contents[index]; };
		
		// For iteration
 		const_iterator begin() const { return contents.begin(); }
 		const_iterator end() const { return contents.end(); }
		
	private:
		vector<T> contents;
};


/* Constructor */
template <typename T> 
Row<T>::Row() {
	lastError = "";
}


/* Overload Row<T> * Row<T>
 * 
 * Returns a sum of products of the corresponding element of 2 rows 
 *
 * std::invalid_argument is thrown if the row lengths do not match
 */
template <typename T>
T Row<T>::operator*(const Row<T>& other) {
	if (contents.size() != other.contents.size()) {
		lastError = "Attempted to multiply 2 rows of different lengths";
		throw std::invalid_argument(lastError);
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

} // end namespace


