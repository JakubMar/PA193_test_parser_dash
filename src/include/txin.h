#pragma once

#include "common.h"
#include <ostream>

class TxIn
{
private:
    uint256 hashPrevTrans;
    uint32_t indexPrevTrans;
    //std::unique_ptr<char[]> script;
    uint32_t seqNumber;
public:
    TxIn(const char* buffer, uint32_t& globalOffset, size_t& unread_size);
    uint32_t GetSeqNumber() const;

    friend std::ostream& operator<< (std::ostream& stream, const TxIn& tin);
    friend class TestHelper;

    void setHashPrevTrans(const uint256 &value);
    void setIndexPrevTrans(const uint32_t &value);
    void setSeqNumber(const uint32_t &value);

private:
    TxIn() {}
};

