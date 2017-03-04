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

namespace Mach { 
	template <typename T> class Row; // forward declaration necessary
	const size_t hwThreads = std::thread::hardware_concurrency();
}
 
typedef long double MachDouble;

