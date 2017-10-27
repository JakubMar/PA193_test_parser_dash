#include "transaction.h"

Transaction::Transaction(const char *buffer, uint32_t &globalOffset) : beginEndOffsets(offsets(0,0))
{
    uint32_t localOffset = 0;

    version = ParseUint32(buffer);
    localOffset += VERSION_SIZE;

    varInt txInCount = ParseVarLength(reinterpret_cast<const unsigned char*>(buffer + localOffset));
    localOffset += txInCount.second;
    for(size_t i = 0; i < txInCount.first; ++i)
    {
        inTrans.emplace_back(TxIn(buffer+localOffset, localOffset));
    }

    varInt txOutCount = ParseVarLength(reinterpret_cast<const unsigned char*>(buffer + localOffset));
    localOffset += txOutCount.second;
    for(size_t i = 0; i < txOutCount.first; ++i)
    {
        outTrans.emplace_back(TxOut(buffer+localOffset, localOffset));
    }

    lockTime = ParseUint32(buffer);
    localOffset += TIME_SIZE;

    beginEndOffsets = offsets(globalOffset, localOffset);
    globalOffset += localOffset;
}

const offsets Transaction::GetOffsets() const
{
    return beginEndOffsets;
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

