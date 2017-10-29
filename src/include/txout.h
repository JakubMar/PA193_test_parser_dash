#pragma once

#include "common.h"
#include <ostream>


class TxOut
{
private:
    uint64_t value;
    std::unique_ptr<char[]> script;
public:
    TxOut(const char* buffer, uint32_t& globalOffset, size_t unread_size);

    friend std::ostream& operator<< (std::ostream& stream, const TxOut& tout);
};

