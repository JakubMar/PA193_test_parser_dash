#pragma once

#include "parserexception.h"

/**
 * @brief MagicNumberException is an exception class
 * that inherits from ParserException.
 *
 * This exception is thrown when the it's detected that a block being read
 * doesn't start with dash's magic number. If this exception is thrown, block
 * is invalid and should not be further read.
 */
class MagicNumberException: public ParserException
{
public:

    MagicNumberException() : ParserException("Block does not start with magic number") {}

    MagicNumberException(std::string what) : ParserException(what) {}
};
