/* MachMatrix.cpp
 * 
 * Author: Cliff Chandler <cliffplaysdrums@gmail.com>
 *
 * License: GPL
 */
 
 /* TODO:
  * Return int from push_back for error checking.
  */
 
 #include <iostream>
  
 namespace Mach {
  
 using std::cout;
 using std::endl;
 
 template <typename T> 
 class MachMatrix {
 
 	// typename is mandatory before a qualified dependent type
 	typedef typename vector<Row<T>>::iterator iterator;
	typedef typename vector<Row<T>>::const_iterator const_iterator;
 	
 	public:
 		
 		// Constructors
 		MachMatrix() {};
 		MachMatrix(const size_t rowCount) : matrix(rowCount) {};
 		MachMatrix(const vector<Row<T> >& copyFrom) { matrix = copyFrom; }
 		
 		// Common vector functions
 		void push_back(const Row<T>& r) { matrix.push_back(r); }
 		size_t size() const { return matrix.size(); }
 		bool empty() const { return matrix.empty(); }
 		void reserve(size_t n) { matrix.reserve(n); };
 		void resize(size_t n) { matrix.resize(n); };
 		void resize(size_t n, Row<T> r) { matrix.resize(n, r); };
 		
 		// Useful functions
 		MachMatrix<T> transpose() const;
 		MachMatrix<T> timesTransposeOf(const MachMatrix<T>&) const;
 		
 		// Operator overloading
 		Row<T> operator[](const size_t index) const { return matrix[index]; }
 		MachMatrix<T> operator*(const MachMatrix<T>&) const;
 		MachMatrix<T> parallelMultiply(const MachMatrix<T>&) const; // this will replace operator*
 		
 		// For iteration
 		const_iterator begin() const { return matrix.begin(); }
 		const_iterator end() const { return matrix.end(); }
 
 	private:
 		vector<Row<T> > matrix;
 		
 		// Helper functions
		Row<T> parMulHelp(const MachMatrix<T> matB, const size_t rowA) const;
 };
 
 
 /* Multiplies this MachMatrix by the transpose of another
  *
  * This is faster than transposing and then performing matrix multiplication
  */
 template <typename T>
 MachMatrix<T> MachMatrix<T>::timesTransposeOf(const MachMatrix<T>& matB) const {
 	// Dimensions
 	// A: (M x N)  |  B: (K x N)  |  B transposed: (N x K)  |  C: (N x K)
 	MachMatrix<T> result;
 	for (Row<T> rowA : matrix) {
 		Row<T> rowC;
 		for (Row<T> rowB : matB) {
 			rowC.push_back(rowA * rowB);
 		}
 		
 		result.push_back(rowC);
 	}
 	
 	return result;
 }
 
 
 /* Transpose a MachMatrix
  *
  * std::invalid_argument is thrown if the matrix is empty
  */
 template <typename T>
 MachMatrix<T> MachMatrix<T>::transpose() const {
 	// Check if matrix is empty
 	if (matrix.empty()) {
 		throw std::invalid_argument("Attempted to transpose empty matrix.");
 	}
 	
 	MachMatrix<T> transposedMatrix;
 	transposedMatrix.reserve(matrix[0].size()); // preallocate memory
 	// transpose
 	for (size_t col=0; col<matrix[0].size(); col++) {
 		Row<T> r;
 		
 		for (size_t row=0; row<matrix.size(); row++) {
 			r.push_back(matrix[row][col]);
 		}
 		
 		transposedMatrix.push_back(r);
 	}
 	
 	return transposedMatrix;
 }
 
 
 /* Overload MachMatrix * MachMatrix to perform matrix multiplication
  *
  * std::invalid_argument is thrown if:
  *   - either matrix is empty
  *   - the inner dimensions of the matrices don't match
  */
 template <typename T>
 MachMatrix<T> MachMatrix<T>::operator*(const MachMatrix<T>& matB) const {
 	// Check if either argument is empty
 	if (matrix.empty() || matB.empty()) {
 		throw std::invalid_argument("One of the matrices was empty.");
 	}
 	// Check inner matrix dimensions
 	if (matrix[0].size() != matB.size()) {
 		throw std::invalid_argument("Inner dimensions of matrices must match when multiplying.");
 	}
 	
 	size_t numRowsA = matrix.size();
 	size_t numColumnsA = matrix[0].size();
 	size_t numColumnsB = matB[0].size();
 	MachMatrix<T> result;
 	
 	// Multiply
 	for (size_t i = 0; i < numRowsA; i++) {
 		Row<T> r;
 		for (size_t j = 0; j < numColumnsB; j++) {
	 		T sumOfProducts = 0;
	 		
 			for (size_t k = 0; k < numColumnsA; k++) {
 				sumOfProducts += matrix[i][k] * matB[k][j];
 			}
 			
 			r.push_back(sumOfProducts);
 		}
 		
 		result.push_back(r);
 	}
 	
 	return result;
 }
 
 
 template <typename T>
 MachMatrix<T> MachMatrix<T>::parallelMultiply(const MachMatrix<T>& matB) const {
 	// Check if either argument is empty
 	if (matrix.empty() || matB.empty()) {
 		throw std::invalid_argument("One of the matrices was empty.");
 	}
 	// Check inner matrix dimensions
 	if (matrix[0].size() != matB.size()) {
 		string errorMsg = "Inner dimensions of matrices must match when multiplying.";
		errorMsg.append(" Thrown from MachMatrix<T>::parallelMultiply()");
 		throw std::invalid_argument(errorMsg);
 	}
 	
 	size_t numRowsA = matrix.size();
 	//size_t numColumnsA = matrix[0].size();
 	size_t numColumnsB = matB[0].size();
 	//size_t interval = numRowsA / hwThreads;
 	MachMatrix<T> result;
 	Row<T> r(numColumnsB);
 	result.reserve(numRowsA);
 	vector<std::future<Row<T>>> handles;
 	
 	// NOTE: This is only faster when there are more rows than hardware threads
 	for (size_t ix = 0; ix < numRowsA; ix++) {
 		handles.push_back(std::async(std::launch::async, 
 			&MachMatrix<T>::parMulHelp, this, matB.transpose(), ix));
 	}
 	
 	for (size_t ix =0; ix < numRowsA; ix++) {
 		result.push_back(handles[ix].get());
 	}
 	
 	return result;
 	
 }
 
 // Assumes matB has already been transposed for faster memory access
 template <typename T>
 Row<T> MachMatrix<T>::parMulHelp(const MachMatrix<T> matB, const size_t rowA) 
 	const
 {
	Row<T> r;
	for (size_t rowB = 0; rowB < matB.size(); rowB++) {
		r.push_back(matrix[rowA] * matB[rowB]);
	}
	 
	 return r;
 }
 
 } // end namespace
 
