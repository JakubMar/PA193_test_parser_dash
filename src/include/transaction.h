#pragma once

#include "txin.h"
#include "txout.h"
#include <vector>

/**
 * @brief The Transaction class data structure for holding TxIn(s) and TxOut(s)
 */
class Transaction
{
private:
    uint32_t version;
    std::vector<TxIn> inTrans;
    std::vector<TxOut> outTrans;
    uint32_t lockTime;
    offsets beginEndOffsets;

public:
    /**
     * @brief Transaction Constructor of data holding structure
     * @param buffer memory to parse to corrsponding values
     * @param globalOffset offset to set current position for parsing other transactions from the same buffer
     * @param unread_size size of unread part of buffer
     */
    Transaction(const char* buffer, uint32_t& globalOffset, size_t &unread_size);

    /**
     * @brief getOffsets getter for private member: offsets
     * @return offsets
     */
    const offsets getOffsets() const;

    /**
     * @brief getVersion getter for private member: version
     * @return version
     */
    uint32_t getVersion() const;

    /**
     * @brief getInputs getter for private member: vector of input transactions
     * @return vector of TxIn
     */
    const std::vector<TxIn>& getInputs() const;

    /**
     * @brief getOutputs getter for private member: vector of output transactions
     * @return vector of TxOut
     */
    const std::vector<TxOut>& getOutputs() const;

    /**
     * @brief getLockTime getter for private member: lock time
     * @return lockTime
     */
    uint32_t getLockTime() const;

    /**
     * @brief operator << overloaded operator for printing the data
     * @param stream stream to write
     * @param t transaction to print
     * @return stream
     */
    friend std::ostream& operator<<(std::ostream& stream, const Transaction& t);

    /**
     * @brief friend class for testing
     */
    friend class TestHelper;

private:
    Transaction() {}
};
