#ifndef MYERRORS
#define MYERRORS
// custom exceptions

#include <exception> // std::exception

class FileOpenError : public std::exception
{
	const char* file;
	public:
		FileOpenError(const char*);
		virtual const char* what() const throw ();
};

#endif
