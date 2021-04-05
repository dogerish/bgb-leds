#ifndef FILES
#define FILES
#include <fstream>
#include "errors.h"
// functions for dealing with files

// open streamatype file stream
template<typename streamtype, typename T>
streamtype openfs(T fn)
{
	streamtype f(fn);
	if (f.fail()) throw FileOpenError(fn);
	return f;
}
// open input file stream
template<typename T>
std::ifstream openifs(T fn) { return openfs<std::ifstream>(fn); }
// open output file stream
template<typename T>
std::ofstream openofs(T fn) { return openfs<std::ofstream>(fn); }

#endif
