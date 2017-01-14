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

typedef long double MachDouble;

template <typename T> class Row;
typedef std::vector<Row<MachDouble> > MachMatrix;

typedef std::vector<MachDouble>
