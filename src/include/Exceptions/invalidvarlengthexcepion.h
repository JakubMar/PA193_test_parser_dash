#pragma once

#include "parserexception.h"

class InvalidVarLengthException: public ParserException
{
public:

    InvalidVarLengthException() : ParserException("Size of block is invalid") {}

    InvalidVarLengthException(std::string what) : ParserException(what) {}
};

