#pragma once

#include <iostream>
#include <exception>
#include <stdexcept>
#include <sstream>

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
