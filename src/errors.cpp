#include "errors.h"

FileOpenError::FileOpenError(const char* file) { this->file = file; }
const char* FileOpenError::what() const throw () { return file; }
