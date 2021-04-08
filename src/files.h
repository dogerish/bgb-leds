#ifndef FILES
#define FILES
// functions for dealing with files

#include <string>   // std::string
#include <fstream>  // std::ifstream std::ofstream
#include "errors.h" // FileOpenError

// open streamatype file stream
template<typename streamtype, typename T>
streamtype openfs(T fn)
{
	streamtype f(fn);
	if (f.fail())
	{
		std::string tmp(fn);
		throw FileOpenError(tmp.c_str());
	}
	return f;
}
// open input file stream
template<typename T>
std::ifstream openifs(T fn) { return openfs<std::ifstream>(fn); }
// open output file stream
template<typename T>
std::ofstream openofs(T fn) { return openfs<std::ofstream>(fn); }

#endif
