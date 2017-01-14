/* Row.cpp
 * 
 * Author: Cliff Chandler <cliffplaysdrums@gmail.com>
 *
 * License: GPL
 *
 * This class is a data structure for holding rows of a matrix and providing
 * added functionality such as multiplication of whole rows
 */
 
#include "headers.h"
 
template <typename T> class Row {
	public:
		std::vector<T> contents;
		Row();
		T multiply(Row);
}

Row::Row() {

}

template <typename T>
Row::T multiply(Row r) {
	return 0;
}
