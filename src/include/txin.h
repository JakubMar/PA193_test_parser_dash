#pragma once

#include "common.h"
#include <ostream>

/**
 * @brief The TxIn class input transaction
 */
class TxIn
{
private:
    /**
     * @brief hashPrevTrans hash of corresponding previous TxOut
     */
    uint256 hashPrevTrans;
    /**
     * @brief indexPrevTrans index of corresponding previous TxOut
     */
    uint32_t indexPrevTrans;
    /**
     * @brief scriptOffsets begin and end offsets of script
     * script is not saved nor parsed
     */
    offsets scriptOffsets;
    /**
     * @brief seqNumber sequence number
     */
    uint32_t seqNumber;

public:
    /**
     * @brief TxIn Constructor of data holding structure
     * @param buffer memory to parse to corrsponding values
     * @param globalOffset offset to set current position for parsing other transactions from the same buffer
     * @param unread_size size of unread part of buffer
     * @throws InvalidTransactionSizeException
     * @throws InvalidScriptSizeException
     */
    TxIn(const char* buffer, uint32_t& globalOffset, size_t& unread_size);

    /**
     * @brief getSeqNumber getter for private member: sequence number
     * @return seqNumber
     */
    uint32_t getSeqNumber() const;

    /**
     * @brief getHashPrevTrans getter for private member: hash of previous out transaction
     * @return hashPrevTrans
     */
    uint256 getHashPrevTrans() const;

    /**
     * @brief operator << overloaded operator for printing the data
     * @param stream stream to write
     * @param tin input transaction to print
     * @return stream
     */
    friend std::ostream& operator<< (std::ostream& stream, const TxIn& tin);

    /**
     * @brief friend class for testing
     */
    friend class TestHelper;

private:
    /**
     * @brief TxIn Constructor for testing
     */
    TxIn() {}
};

