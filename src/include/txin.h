#pragma once

#include "common.h"
#include <ostream>

class TxIn
{
private:
    uint256 hashPrevTrans;
    uint32_t indexPrevTrans;
    offsets scriptOffsets;
    uint32_t seqNumber;
public:
    /**
     * @brief TxIn
     * @param buffer
     * @param globalOffset
     * @param unread_size
     */
    TxIn(const char* buffer, uint32_t& globalOffset, size_t& unread_size);

    /**
     * @brief getSeqNumber
     * @return
     */
    uint32_t getSeqNumber() const;

    /**
     * @brief getHashPrevTrans
     * @return
     */
    uint256 getHashPrevTrans() const;

    /**
     * @brief operator <<
     * @param stream
     * @param tin
     * @return
     */
    friend std::ostream& operator<< (std::ostream& stream, const TxIn& tin);

    /**
     *
     */
    friend class TestHelper;

private:
    TxIn() {}
};

