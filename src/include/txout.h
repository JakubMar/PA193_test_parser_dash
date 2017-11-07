#pragma once

#include "common.h"
#include <ostream>


class TxOut
{
private:
    uint64_t value;
    offsets scriptOffsets;
public:
    /**
     * @brief TxOut
     * @param buffer
     * @param globalOffset
     * @param unread_size
     */
    TxOut(const char* buffer, uint32_t& globalOffset, size_t &unread_size);

    /**
     * @brief getValue
     * @return
     */
    uint64_t getValue() const;

    /**
     * @brief operator <<
     * @param stream
     * @param tout
     * @return
     */
    friend std::ostream& operator<< (std::ostream& stream, const TxOut& tout);

    /**
     *
     */
    friend class TestHelper;

private:
    TxOut() {}
};

