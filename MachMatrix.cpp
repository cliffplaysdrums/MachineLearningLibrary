/* MachMatrix.cpp
 * 
 * Author: Cliff Chandler <cliffplaysdrums@gmail.com>
 *
 * License: GPL
 */
 
 /* TODO:
  * Return int from push_back for error checking.
  */
  
 
 template <typename T> class MachMatrix {
 	public:
 		string lastError;
 		
 		MachMatrix() { lastError = ""; }
 		
 		// common vector functions
 		void push_back(Row<T>& r) { matrix.push_back(r); }
 		size_t size() { return matrix.size(); }
 		bool empty() { return matrix.empty(); }
 		
 		Row<T> operator[](size_t); // overload [] operator for class
 		MachMatrix<T> operator*(const MachMatrix<T>&); // overload matrix multiplication
 
 	private:
 		vector<Row<T> > matrix;
 };
 
 
 // Overload []
 template <typename T>
 Row<T> MachMatrix<T>::operator[](size_t index) {
 	return matrix[index];
 }
 
 
 // Matrix multiplication
 template <typename T>
 MachMatrix<T> MachMatrix<T>::operator*(const MachMatrix<T>& matB) {
 	if (matrix.size() < 1 || matB.empty()) {
 		lastError = "One of the matrices was empty.";
 		return NULL;
 	}
 	
 	if (matrix[0].size() != matB.size() {
 		lastError = "Inner dimensions of matrices must match when multiplying.";
 		return NULL;
 	}
 	
 	size_t numRowsA = matrix.size();
 	size_t numColumnsB = matB[0].size();
 	MachMatrix<T> result;
 	
 	for (size_t i = 0; i < numRowsA; i++) {
 		Row<T> r;
 		for (size_t j = 0; j < numColumnsB; j++) {
	 		T sumOfProducts = 0;
	 		
 			for (size_t k = 0; k < numColumnsB; k++) {
 				sumOfProducts += matrix[i][k] * matB[k][i];
 			}
 			
 			r.push_back(sumOfProducts);
 		}
 		
 		result.push_back(r);
 	}
 }
 
