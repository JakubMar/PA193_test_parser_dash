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
    const offsets GetOffsets() const;
    uint32_t GetVersion() const;
    const std::vector<TxIn>& GetInputs() const;
    const std::vector<TxOut>& GetOutputs() const;
    uint32_t GetLockTime() const;
    void setVersion(const uint32_t &value);
    void setInTrans(const std::vector<TxIn> &value);
    void setOutTrans(const std::vector<TxOut> &value);
    void setLockTime(const uint32_t &value);
    void setBeginEndOffsets(const offsets &value);

    friend class TestHelper;

private:
    Transaction() {}
};
