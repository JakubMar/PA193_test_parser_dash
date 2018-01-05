#pragma once

#include "parserexception.h"

/**
 * @brief InvalidTransactionSizeException is an exception class
 * that inherits from ParserException.
 *
 * This exception is thrown when the it's detected that a size of
 * a transaction being read is invalid. If this exception is thrown, block
 * is invalid and should not be further read.
 */
class InvalidTransactionSizeException: public ParserException
{
public:

    InvalidTransactionSizeException() : ParserException("Size of transaction is invalid") {}

    InvalidTransactionSizeException(std::string what) : ParserException(what) {}
};

