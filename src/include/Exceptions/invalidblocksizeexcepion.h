#pragma once

#include "parserexception.h"

/**
 * @brief InvalidBlockSizeException is an exception class
 * that inherits from ParserException.
 *
 * This exception is thrown when the it's detected that a size of
 * a block being read is invalid. If this exception is thrown, block
 * is invalid and should not be further read.
 */
class InvalidBlockSizeException: public ParserException
{
public:

    InvalidBlockSizeException() : ParserException("Size of block is invalid") {}

    InvalidBlockSizeException(std::string what) : ParserException(what) {}
};

