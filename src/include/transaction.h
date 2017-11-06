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
    Transaction(const char* buffer, uint32_t& globalOffset, size_t &unread_size);
    friend std::ostream& operator<<(std::ostream& stream, const Transaction& t);
    const offsets getOffsets() const;
    uint32_t getVersion() const;
    const std::vector<TxIn>& getInputs() const;
    const std::vector<TxOut>& getOutputs() const;
    uint32_t getLockTime() const;

    friend class TestHelper;

private:
    Transaction() {}
};
