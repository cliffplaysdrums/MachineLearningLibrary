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
  *	Consider making 'contents' private.
  *	Make push_back check for error and return int
  */
 
#include "headers.h"
 
template <typename T> class Row {
	public:
		std::vector<T> contents;
		
		Row();
		void push_back(T);
		T multiply(Row);
		void pop_back();
};

template <typename T> 
Row<T>::Row() {

}

template <typename T>
void Row<T>::push_back(T item) {
	contents.push_back(item);
}

template <typename T>
T Row<T>::multiply(Row<T> r) {
	return 0;
}

template <typename T>
void Row<T>::pop_back() {
	contents.pop_back();
}
