#ifndef READFILEEXCEPTION
#define READFILEEXCEPTION

#include "parserexception.h"

class ReadFileException: public ParserException {
public:

  ReadFileException() : ParserException("Reading from file failed") {}

  ReadFileException(std::string what) : ParserException(what) {}
};

#endif // READFILEEXCEPTION

