#pragma once

#include "parserexception.h"

class InvalidScriptSizeException: public ParserException
{
public:

    InvalidScriptSizeException() : ParserException("Size of script is invalid") {}

    InvalidScriptSizeException(std::string what) : ParserException(what) {}
};

