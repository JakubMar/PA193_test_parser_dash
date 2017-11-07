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
    /**
     * @brief Transaction
     * @param buffer
     * @param globalOffset
     * @param unread_size
     */
    Transaction(const char* buffer, uint32_t& globalOffset, size_t &unread_size);

    /**
     * @brief getOffsets
     * @return
     */
    const offsets getOffsets() const;

    /**
     * @brief getVersion
     * @return
     */
    uint32_t getVersion() const;

    /**
     * @brief getInputs
     * @return
     */
    const std::vector<TxIn>& getInputs() const;

    /**
     * @brief getOutputs
     * @return
     */
    const std::vector<TxOut>& getOutputs() const;

    /**
     * @brief getLockTime
     * @return
     */
    uint32_t getLockTime() const;

    /**
     * @brief operator <<
     * @param stream
     * @param t
     * @return
     */
    friend std::ostream& operator<<(std::ostream& stream, const Transaction& t);

    /**
     *
     */
    friend class TestHelper;

private:
    Transaction() {}
};
