#ifndef MYERRORS
#define MYERRORS
#include <exception>
// custom exceptions
class FileOpenError : public std::exception
{
	const char* file;
	public:
		FileOpenError(const char*);
		virtual const char* what() const throw ();
};

#endif
