#pragma once

#include "parserexception.h"

/**
 * @brief InvalidScriptSizeException is an exception class
 * that inherits from ParserException.
 *
 * This exception is thrown when the it's detected that a size of
 * a script being read is invalid. If this exception is thrown, block
 * is invalid and should not be further read.
 */
class InvalidScriptSizeException: public ParserException
{
public:

    InvalidScriptSizeException() : ParserException("Size of script is invalid") {}

    InvalidScriptSizeException(std::string what) : ParserException(what) {}
};

