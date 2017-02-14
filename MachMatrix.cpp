/* MachMatrix.cpp
 * 
 * Author: Cliff Chandler <cliffplaysdrums@gmail.com>
 *
 * License: GPL
 */
 
 /* TODO:
  * Return int from push_back for error checking.
  */
  
 #include <stdexcept>
 
 template <typename T> class MachMatrix {
 	public:
 		string lastError;
 		
 		// Constructors
 		MachMatrix() { lastError = ""; }
 		MachMatrix(const vector<Row<T> >& copyFrom) {
 			lastError = "";
 			matrix = copyFrom;
 		}
 		// Common vector functions
 		void push_back(Row<T>& r) { matrix.push_back(r); hasBeenTransposed = false; }
 		size_t size() const { return matrix.size(); }
 		bool empty() const { return matrix.empty(); }
 		
 		// Useful functions
 		MachMatrix<T> transpose();
 		
 		// Operator overloading
 		Row<T> operator[](size_t index) const { return matrix[index]; }
 		MachMatrix<T> operator*(const MachMatrix<T>&);
 
 	private:
 		vector<Row<T> > matrix;
 		vector<Row<T> > transposedMatrix;
 		bool hasBeenTransposed = false; // flag so that transpose() only runs when necessary
 };
 
 
 /* Transpose a MachMatrix
  *
  * std::invalid_argument is thrown if the matrix is empty
  * 
  * The transposed matrix is saved internally, so if the matrix is not
  * modified, the transpose can be returned immediately.
  */
 template <typename T>
 MachMatrix<T> MachMatrix<T>::transpose() {
 	// Check if matrix is empty
 	if (matrix.empty()) {
 		lastError = "Attempted to transpose empty matrix.";
 		throw std::invalid_argument(lastError);
 	} else if (hasBeenTransposed) { 
 	// transpose already exists
 		return transposedMatrix;
 	}
 	
 	if (!transposedMatrix.empty()) {
 	// Transpose of older matrix version exists
 		transposedMatrix.clear(); // Clear old contents
 		transposedMatrix.resize(matrix[0].size()); // Avoid future resizing
 	}
 	
 	// transpose
 	for (size_t col=0; col<matrix[0].size(); col++) {
 		Row<T> r;
 		
 		for (size_t row=0; row<matrix.size(); row++) {
 			r.push_back(matrix[row][col]);
 		}
 		
 		transposedMatrix.push_back(r);
 	}
 	
 	hasBeenTransposed = true;
 	
 	return MachMatrix<T>(transposedMatrix);
 }
 
 
 /* Overload MachMatrix * MachMatrix to perform matrix multiplication
  *
  * std::invalid_argument is thrown if:
  *   - either matrix is empty
  *   - the inner dimensions of the matrices don't match
  */
 template <typename T>
 MachMatrix<T> MachMatrix<T>::operator*(const MachMatrix<T>& matB) {
 	// Check if either argument is empty
 	if (matrix.empty() || matB.empty()) {
 		lastError = "One of the matrices was empty.";
 		throw std::invalid_argument(lastError);
 	}
 	
 	// Check inner matrix dimensions
 	if (matrix[0].size() != matB.size()) {
 		lastError = "Inner dimensions of matrices must match when multiplying.";
 		throw std::invalid_argument(lastError);
 	}
 	
 	size_t numRowsA = matrix.size();
 	size_t numColumnsB = matB[0].size();
 	MachMatrix<T> result;
 	
 	// Multiply
 	for (size_t i = 0; i < numRowsA; i++) {
 		Row<T> r;
 		for (size_t j = 0; j < numColumnsB; j++) {
	 		T sumOfProducts = 0;
	 		
 			for (size_t k = 0; k < numColumnsB; k++) {
 				sumOfProducts += matrix[i][k] * matB[k][j];
 			}
 			
 			r.push_back(sumOfProducts);
 		}
 		
 		result.push_back(r);
 	}
 	
 	return result;
 }
 
