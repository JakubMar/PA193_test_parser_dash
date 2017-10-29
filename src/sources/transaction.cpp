#include "transaction.h"
#include "invalidtransactionsizeexcepion.h"

Transaction::Transaction(const char *buffer, uint32_t &globalOffset, uint32_t unread_size) : beginEndOffsets(offsets(0,0))
{
    uint32_t localOffset = 0;

    // VERSION
    if(unread_size < VERSION_SIZE)
    {
        throw InvalidTransactionSizeException();
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
        inTrans.emplace_back(TxIn(buffer+localOffset, localOffset, unread_size - localOffset));
    }

    // TxOut(s)
    varInt txOutCount = ParseVarLength(reinterpret_cast<const unsigned char*>(buffer + localOffset), unread_size);
    localOffset += txOutCount.second;
    unread_size -= txOutCount.second;

    for(size_t i = 0; i < txOutCount.first; ++i)
    {
        outTrans.emplace_back(TxOut(buffer+localOffset, localOffset, unread_size - localOffset));
    }

    // LOCK_TIME
    if(unread_size < TIME_SIZE)
    {
        throw InvalidTransactionSizeException();
    }
    lockTime = ParseUint32(buffer);
    localOffset += TIME_SIZE;

    //Begin_End_Offsets
    beginEndOffsets = offsets(globalOffset, localOffset);
    globalOffset += localOffset;
}

std::ostream& operator<<(std::ostream& stream, const Transaction& t)
{
    stream << "-------TRANSACTION-------: " << std::endl;
    stream << "TxIn:" << std::endl;
    for(auto& it : t.inTrans)
    {
        stream << "/t" << it << std::endl;
    }

    stream << "TxOut:" << std::endl;
    for(auto& it : t.outTrans)
    {
        stream << "/t" << it << std::endl;
    }

    return stream;
}

