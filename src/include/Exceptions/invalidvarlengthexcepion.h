#pragma once

#include "parserexception.h"

/**
 * @brief InvalidVarLengthException is an exception class
 * that inherits from ParserException.
 *
 * This exception is thrown when the it's detected that a variable length
 * integer's length is invalid. If this exception is thrown, block
 * is invalid and should not be further read.
 */
class InvalidVarLengthException: public ParserException
{
public:

    InvalidVarLengthException() : ParserException("Size of block is invalid") {}

    InvalidVarLengthException(std::string what) : ParserException(what) {}
};

