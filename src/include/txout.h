#pragma once

#include "common.h"
#include <ostream>


class TxOut
{
private:
    uint64_t value;
    //std::unique_ptr<char[]> script;
public:
    TxOut(const char* buffer, uint32_t& globalOffset);
    uint64_t GetValue() const;

    friend std::ostream& operator<< (std::ostream& stream, const TxOut& tout);
    friend class TestHelper;

private:
    TxOut() {}
};

