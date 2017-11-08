#pragma once

#include "common.h"
#include <ostream>

/**
 * @brief The TxOut class output transaction
 */
class TxOut
{
private:
    /**
     * @brief value value in in DASH * 10^8
     */
    uint64_t value;
    /**
     * @brief scriptOffsets begin and end offsets of script
     * script is not saved nor parsed
     */
    offsets scriptOffsets;

public:
    /**
     * @brief TxOut Constructor of data holding structure
     * @param buffer memory to parse to corrsponding values
     * @param globalOffset offset to set current position for parsing other transactions from the same buffer
     * @param unread_size size of unread part of buffer
     */
    TxOut(const char* buffer, uint32_t& globalOffset, size_t &unread_size);

    /**
     * @brief getValue getter for private member: value in DASH * 10^8
     * @return value
     */
    uint64_t getValue() const;

    /**
     * @brief operator << overloaded operator for printing the data
     * @param stream stream to write
     * @param tout output transaction to print
     * @return stream
     */
    friend std::ostream& operator<< (std::ostream& stream, const TxOut& tout);

    /**
     * @brief friend class for testing
     */
    friend class TestHelper;

private:
    /**
     * @brief TxOut Constructor for testing
     */
    TxOut() {}
};

