#pragma once

#include "parserexception.h"

class InvalidScriptkSizeException: public ParserException {
public:

  InvalidScriptkSizeException() : ParserException("Size of script is invalid") {}

  InvalidScriptkSizeException(std::string what) : ParserException(what) {}
};

