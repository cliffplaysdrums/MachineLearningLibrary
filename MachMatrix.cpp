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
 		void push_back(Row<T>);
 		size_t size() { return matrix.size(); }
 		bool empty() { return matrix.empty(); }
 		
 		Row<T> operator[](size_t); // overload [] operator for class
 		MachMatrix<T> operator*(const MachMatrix<T>&); // overload matrix multiplication
 
 	private:
 		vector<Row<T> > matrix;
 };
 
 
 template <typename T>
 void MachMatrix<T>::push_back(Row<T> r) {
 	matrix.push_back(r);
 }
 
 
 template <typename T>
 Row<T> MachMatrix<T>::operator[](size_t index) {
 	return matrix[index];
 }
 
 
 template <typename T>
 MachMatrix<T> MachMatrix<T>::operator*(const MachMatrix<T>& mat) {
 	if (matrix.size() < 1 || mat.empty()) {
 		lastError = "One of the matrices was empty.";
 		return NULL;
 	}
 	
 	if (matrix[0].size() != mat.size() {
 		lastError = "Inner dimensions of matrices must match when multiplying.";
 		return NULL;
 	}
 }
 
