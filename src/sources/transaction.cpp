#include "transaction.h"
#include "invalidtransactionsizeexcepion.h"
#include <ctime>
#include <iostream>

Transaction::Transaction(const char *buffer, uint32_t &globalOffset, size_t &unread_size) : beginEndOffsets(offsets(0,0))
{
    uint32_t localOffset = 0;

    // VERSION
    if(unread_size < VERSION_SIZE)
    {
        throw InvalidTransactionSizeException("Invalid read of Version");
    }
    version = ParseUint32(buffer);
    localOffset += VERSION_SIZE;
    unread_size -= VERSION_SIZE;

    // TxIn(s)
    varInt txInCount = ParseVarLength(reinterpret_cast<const unsigned char*>(buffer + localOffset), unread_size);
    localOffset += txInCount.second;
    unread_size -= txInCount.second;
    for(size_t i = 0; i < txInCount.first; ++i)
    {
        inTrans.emplace_back(TxIn(buffer+localOffset, localOffset, unread_size));
    }

    // TxOut(s)
    varInt txOutCount = ParseVarLength(reinterpret_cast<const unsigned char*>(buffer + localOffset), unread_size);
    localOffset += txOutCount.second;
    unread_size -= txOutCount.second;

    for(size_t i = 0; i < txOutCount.first; ++i)
    {
        outTrans.emplace_back(TxOut(buffer+localOffset, localOffset, unread_size));
    }

    // LOCK_TIME
    if(unread_size < TIME_SIZE)
    {
        throw InvalidTransactionSizeException("Invalid read of Time");
    }
    lockTime = ParseUint32(buffer+localOffset);
    localOffset += TIME_SIZE;
    unread_size -= TIME_SIZE;

    //Begin_End_Offsets
    beginEndOffsets = offsets(globalOffset, localOffset);
    globalOffset += localOffset;
}


const offsets Transaction::getOffsets() const
{
    return beginEndOffsets;
}

uint32_t Transaction::getVersion() const
{
    return version;
}

const std::vector<TxIn>& Transaction::getInputs() const
{
    return inTrans;
}

const std::vector<TxOut>& Transaction::getOutputs() const
{
    return outTrans;
}

uint32_t Transaction::getLockTime() const
{
    return lockTime;
}

void Transaction::setVersion(const uint32_t &value)
{
    version = value;
}

void Transaction::setInTrans(const std::vector<TxIn> &value)
{
    inTrans = value;
}

void Transaction::setOutTrans(const std::vector<TxOut> &value)
{
    outTrans = value;
}

void Transaction::setLockTime(const uint32_t &value)
{
    lockTime = value;
}

void Transaction::setBeginEndOffsets(const offsets &value)
{
    beginEndOffsets = value;
}

std::ostream& operator<<(std::ostream& stream, const Transaction& t)
{
    stream << "  -------TRANSACTION-------: " << std::endl;
    stream << "  Version: " << t.version << std::endl;
    std::time_t time = t.lockTime;
    stream << "  Time: " << std::asctime(std::localtime(&time));
    stream << "  TxIn(s):" << std::endl;
    for(auto& it : t.inTrans)
    {
        stream << "\t" << it << std::endl;
    }

    stream << "  TxOut(s):" << std::endl;
    for(auto& it : t.outTrans)
    {
        stream << "\t" << it << std::endl;
    }

    return stream;
}

