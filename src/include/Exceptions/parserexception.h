#pragma once

#include <iostream>
#include <exception>
#include <stdexcept>
#include <sstream>

/**
 * @brief Base exception class for other exceptions to inherit from.
 *
 * The parser uses this exception class to polymorphise other related 
 * exceptions such as InvalidTransactionSizeException,
 * InvalidBlockSizeException, and more. Anytime such an exception is
 * thrown, execution should be stopped either because file could not
 * be read or the blockchain being read is invalid.
 */
class ParserException: public std::exception
{

    std::string nWhat;

public:

    ParserException() : std::exception() {}

    ParserException(std::string what) : nWhat(what) {}

    virtual const char* what() const noexcept
    {
        return nWhat.c_str();
    }
};
