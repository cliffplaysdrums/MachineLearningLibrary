/* types.h
 * 
 * Author: Cliff Chandler <cliffplaysdrums@gmail.com>
 *
 * License: GPL
 *
 * This header contains custom types used by my machine learning library.
 * By default, Mach containers use the long double type.
 */

/* Future Possibilities:
 *
 * Add non-double containers (e.g. MachMatrix_i for int)
 */

using std::string;
using std::vector;

template <typename T> class Row; // forward declaration necessary
 
typedef long double MachDouble;
//typedef vector<Row<MachDouble> > MachMatrix;
