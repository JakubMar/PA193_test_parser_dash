#pragma once

#include "parserexception.h"

class InvalidTransactionSizeException: public ParserException {
public:

  InvalidTransactionSizeException() : ParserException("Size of transaction is invalid") {}

  InvalidTransactionSizeException(std::string what) : ParserException(what) {}
};

