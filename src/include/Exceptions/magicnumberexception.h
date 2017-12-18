#pragma once

#include "parserexception.h"

class MagicNumberException: public ParserException
{
public:

    MagicNumberException() : ParserException("Block does not start with magic number") {}

    MagicNumberException(std::string what) : ParserException(what) {}
};
