#pragma once

#include "txin.h"
#include "txout.h"
#include <vector>

class Transaction
{
private:
    uint32_t version;
    std::vector<TxIn> inTrans;
    std::vector<TxOut> outTrans;
    uint32_t lockTime;
    offsets beginEndOffsets;

public:
    Transaction(const char* buffer, uint32_t& globalOffset);
    friend std::ostream& operator<<(std::ostream& stream, const Transaction& t);
    const offsets GetOffsets() const;
};
