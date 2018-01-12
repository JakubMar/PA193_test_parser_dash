#pragma once

#include "parserexception.h"

/**
 * @brief ReadFileException is an exception class that inherits from ParserException.
 *
 * This exception is thrown when file to read blockchain from could not be opened,
 * or when reading the magic number, or the size of the block, or the content of
 * the block fails.
 */
class ReadFileException: public ParserException
{
public:

    ReadFileException() : ParserException("Reading from file failed") {}

    ReadFileException(std::string what) : ParserException(what) {}
};
