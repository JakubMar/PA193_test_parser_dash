#pragma once

#include "parserexception.h"

class InvalidBlockSizeException: public ParserException {
public:

  InvalidBlockSizeException() : ParserException("Size of block is invalid") {}

  InvalidBlockSizeException(std::string what) : ParserException(what) {}
};

